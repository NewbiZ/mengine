#include <mengine/loaders/tga_loader.h>

#include <fstream>
#include <cassert>
#include <cstring>
#include <iostream>

#ifdef __SSSE3__
#  include <xmmintrin.h>
#  include <tmmintrin.h>
#endif

#include <mengine/mengine.h>

namespace mengine
{

// Internal linkage symbols
namespace {
typedef struct __attribute__((__packed__))
{
    uint8_t  id_length;
    uint8_t  color_map_type;
    uint8_t  image_type;
    uint16_t color_map_offset;
    uint16_t color_map_length;
    uint8_t  color_map_entry_size;
    uint16_t x_origin;
    uint16_t y_origin;
    uint16_t width;
    uint16_t height;
    uint8_t  depth;
    uint8_t  image_descriptor;
} header_t;

typedef struct __attribute__((__packed__))
{
    uint32_t extension_offset;
    uint32_t developer_offset;
    char     signature[18];
} footer_t;

typedef struct __attribute__((__packed__))
{
    uint8_t descriptor;
} rlepacket_t;
}

void* load_tga(const std::string& filename, TextureInfo& ti)
{
    // We only support one type of format:
    // 32bits unsigned ints RGBA
    ti.target = GL_TEXTURE_2D;
    ti.level = 0;
    ti.internalFormat = GL_RGBA;
    ti.type = GL_UNSIGNED_BYTE;
    
    std::ifstream ifs(filename.c_str(), std::ifstream::binary);
    assert(ifs && "error: failed to load tga file");

    // Check that the file is TGA2-compliant
#ifndef NDEBUG
    {
        footer_t footer;
        ifs.seekg(-sizeof(footer_t), std::ios::end);
        ifs.read((char*)&footer, sizeof(footer_t));
        //assert(std::strncmp(footer.signature, "TRUEVISION-XFILE.", 18)==0 &&
        //       "error: filetype not supported (legacy TGA1)");
        ifs.seekg(0);
    }
#endif // NDEBUG

    header_t header;

    // Read the whole file header
    ifs.read((char*)&header, sizeof(header_t));

    ti.width = header.width;
    ti.height = header.height;

    assert(header.depth/8==3 || header.depth/8==4 &&
           "error: unsupported tga depth (not 24/32)");
    ti.format = header.depth/8==3 ? GL_RGB : GL_RGBA;

    // We don't care of the ID field
    ifs.ignore(header.id_length);

    // We do not support color maps
    ifs.ignore(header.color_map_length*header.color_map_entry_size);

    // We only support 32 and 24 bpp
    std::size_t data_size = header.width*header.height*header.depth/8;
    
#ifdef __SSSE3__
    // SIMD instructions require 16B aligned operands
    posix_memalign((void**)&ti.data, 16, data_size);
#else
    ti.data = new uint8_t[data_size];
#endif // __SSSE3__

    // Uncompressed, true-color
    if (header.image_type==2)
    {
        // Load the whole image data
        ifs.read((char*)ti.data, data_size);
    }
    // Compressed (RLE), true-color
    else if (header.image_type==10)
    {
        std::size_t npix = 0;
        rlepacket_t packet;
        while (npix<header.width*header.height)
        {
            const uint8_t rle_mask = 0x80;
            // Read the RLE packet header
            ifs.read((char*)&packet, sizeof(rlepacket_t));
            // Read the first reference pixel
            char bgra[4];
            ifs.read(bgra, header.depth/8);
            std::memcpy(ti.data+(header.depth/8)*npix, bgra, header.depth/8);
            ++npix;
            // Unpack the packet descriptor
            uint8_t count = packet.descriptor & ~rle_mask;
            if (packet.descriptor & rle_mask)
                for (uint8_t i=0; i<count; ++i)
                    memcpy(ti.data+(header.depth/8)*npix+(header.depth/8)*i,
                           bgra, header.depth/8);
            else // RAW packet
                ifs.read((char*)ti.data+(header.depth/8)*npix,
                         header.depth/8*count);
            npix += count;
        }
    }

#ifdef __SSSE3__
    if (header.depth==32)
    {
      // Shuffling mask (RGBA -> BGRA) x 4, in reverse byte order
      static const __m128i m = _mm_set_epi8(15,12,13,14,11,8,9,10,7,4,5,6,3,0,1,2);
      // Assert pixels will NOT be aliased here
      __m128i* __restrict__ pix = (__m128i*)ti.data;
      // Tile the LHS to match 64B cache line size
      for (; (unsigned char*)pix<ti.data+data_size; pix+=4)
      {
        __m128i p1 = _mm_load_si128(pix);
        __m128i p2 = _mm_load_si128(pix+1);
        __m128i p3 = _mm_load_si128(pix+2);
        __m128i p4 = _mm_load_si128(pix+3);
     
        p1 = _mm_shuffle_epi8(p1, m);
        p2 = _mm_shuffle_epi8(p2, m);
        p3 = _mm_shuffle_epi8(p3, m);
        p4 = _mm_shuffle_epi8(p4, m);
     
        _mm_store_si128(pix,   p1);
        _mm_store_si128(pix+1, p2);
        _mm_store_si128(pix+2, p3);
        _mm_store_si128(pix+3, p4);
      }
    }
    else
#endif // __SSSE3__
    {
        for (uint8_t* pixel = ti.data;
             pixel-ti.data < data_size;
             pixel += header.depth/8)
            std::swap(pixel[0], pixel[2]);
    }

    ifs.close();

    return 0;
}

} // end of namespace 'mengine'

