using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using u8 = System.Byte;
using u16 = System.UInt16;
using u32 = System.UInt32;
using u64 = System.UInt64;

namespace WinTheBeer
{
    class The_Beer_Zip
    {
        public enum BeerZipStatus_t {
            BEERZIP_FAIL = -1,
            BEERZIP_SUCCESS
        }
        private const int LOOK_BUF = 0x7E;
        private const int WIN_BUF = 0x80;
        private const int POINT_BUF = LOOK_BUF;
        private const int MAX_BUF_SIZE = LOOK_BUF + WIN_BUF - 1;

        public struct LZ77_t 
        {
            public u8 dist;
            public u8 len;
            public u8 data;

        };

        public struct LZ77_Buffer_t
        {
            public u8[] buffer;

            public LZ77_Buffer_t(int size)
            {
                buffer = new u8[size];
            }
        };

        private void init_lz77_buffer(u8[] str, ref LZ77_Buffer_t lz77_buffer)
        {
            for (u16 i = 0; i < WIN_BUF; i++)
                lz77_buffer.buffer[i] = 0;
            for (u16 i = 0; i < LOOK_BUF; i++)
                lz77_buffer.buffer[i + WIN_BUF] = str[i];
        }

        private void clear_lz77_buffer(ref LZ77_Buffer_t lz77_buffer)
        {
            for (u16 i = 0; i <= MAX_BUF_SIZE; i++)
                lz77_buffer.buffer[i] = 0;
        }

        private void lz77_buffer_push_back(u8[] str, ref LZ77_Buffer_t lz77_buffer, int pos, long size)
        {
            Shift_LZ77_ME(ref lz77_buffer, 1);
            lz77_buffer.buffer[MAX_BUF_SIZE] = (u8)((pos < size) ? str[pos] : 0);
        }
        
        private LZ77_t lz77_search(ref LZ77_Buffer_t lz77_buffer)
        {
            int __point = POINT_BUF;
            LZ77_t __lz77;
            __lz77.dist = 0;
            __lz77.len = 0;
            __lz77.data = lz77_buffer.buffer[POINT_BUF];
            for(u8 i = 0; i < WIN_BUF; i++)
            {
                if(lz77_buffer.buffer[POINT_BUF] == lz77_buffer.buffer[i])
                {
                    u8 j = 0;
                    while (lz77_buffer.buffer[POINT_BUF + j] == lz77_buffer.buffer[i + j])
                        j++;
                    if (j < __lz77.len)
                        continue;
                    __lz77.dist = (u8)(POINT_BUF - i);
                    __lz77.len = (u8)((i + j > WIN_BUF || lz77_buffer.buffer[POINT_BUF + j] == 0) ? j - i : j);
                    __lz77.data = lz77_buffer.buffer[POINT_BUF + __lz77.len];
                    i += __lz77.len;
                }
            }
            __lz77.dist = (u8)((__lz77.len == 0) ? 0 : __lz77.dist);
            return __lz77;
        }

        public u64 beerSockUnZip(u8[] str, ref List<LZ77_t> lz77_list, long offset, ref u64 size)
        {
            LZ77_Buffer_t __lz77_buffer = new LZ77_Buffer_t(WIN_BUF + LOOK_BUF);
            long string_offset = 0;
            long i = 0;
            clear_lz77_buffer(ref __lz77_buffer);
            for(i = offset; string_offset < 513 && i < lz77_list.Count; i++)
            {
                if(lz77_list[(int)i].len != 0)
                {
                    for(int j = 0; j < lz77_list[(int)i].len; i++)
                    {
                        str[string_offset + j] = __lz77_buffer.buffer[POINT_BUF - lz77_list[(int)i].dist];
                        Shift_LZ77_ME(ref __lz77_buffer, 1);
                    }
                }
                __lz77_buffer.buffer[POINT_BUF] = lz77_list[(int)i].data;
                str[string_offset + lz77_list[(int)i].len] = __lz77_buffer.buffer[POINT_BUF];
                string_offset += lz77_list[(int)i].len + 1;
                Shift_LZ77_ME(ref __lz77_buffer, 1);
            }
            size = (u8)string_offset;
            return (u64)(i - offset);
        }

        public BeerZipStatus_t beerSockZip(u8[] str, ref List<LZ77_t> lz77_list, long size)
        {
            LZ77_Buffer_t __buffer = new LZ77_Buffer_t(WIN_BUF + LOOK_BUF);
            init_lz77_buffer(str, ref __buffer);
            for(int i = 0; i < size; i++)
            {
                LZ77_t lz77_data;
                lz77_data = lz77_search(ref __buffer);
                for (int j = i; j <= i + lz77_data.len; j++)
                    lz77_buffer_push_back(str, ref __buffer, j + LOOK_BUF, size);
                i += lz77_data.len;
                lz77_list.Insert(lz77_list.Count, lz77_data);
            }
            return BeerZipStatus_t.BEERZIP_SUCCESS;
        }

        public LZ77_Buffer_t Shift_LZ77(LZ77_Buffer_t my, int n)
        {
            LZ77_Buffer_t lz_buffer = my;
            for (int i = n; i < WIN_BUF + LOOK_BUF; i++)
                lz_buffer.buffer[i - n] = lz_buffer.buffer[i];
            return lz_buffer;
        }

        public LZ77_Buffer_t Shift_LZ77_ME(ref LZ77_Buffer_t my, int n)
        {
            my = Shift_LZ77(my, n);
            return my;
        }
    };
}