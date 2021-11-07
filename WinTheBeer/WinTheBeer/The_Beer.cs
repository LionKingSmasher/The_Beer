using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using u8 = System.Byte;
using u16 = System.UInt16;
using u32 = System.UInt32;
using u64 = System.UInt64;

namespace WinTheBeer
{
    class The_Beer : The_Beer_Zip
    {
        private const u8 COMPRESS_TYPE_STB = 0x01;
        private const u32 STB_HEADER_MAGIC_NUMBER = 0x13631AD2U;

        struct TB_Header_t
        {
            public u32 magicNumber;
            public u32 file_size;
            public u8 compress_type;
        };

        private LZ77_t stb_string_to_list(u8[] buffer)
        {
            LZ77_t __lz77;
            __lz77.dist = buffer[0];
            __lz77.len = buffer[1];
            __lz77.data = buffer[2];
            return __lz77;
        }

        private void stb_list_to_string(List<LZ77_t> list, ref BinaryWriter bw)
        {
            foreach(LZ77_t i in list)
            {
                bw.Write(i.dist);
                bw.Write(i.len);
                bw.Write(i.data);
            }
        }

        private void clear_arr(u8[] arr, int arr_size, u8 val)
        {
            for (int i = 0; i < arr_size; i++)
                arr[i] = val;
        }

        public BeerZipStatus_t compress(String filename)
        {
            // FileInfo filechk = new FileInfo("lz77_compress_test.stb");
            /*
            if (!filechk.Exists) {
                FileStream fs = File.Create(filename);
                fs.Close();
            }
            */
            u16 __i = 0;
            TB_Header_t stb_header;
            List<LZ77_t> lz77_list = new List<LZ77_t>();
            u8[] buffer = new u8[513];
            u64 size = 0;
            // StreamReader sr = new StreamReader(filename);
            // StreamWriter sw = new StreamWriter("lz77_compress_test.stb");
            BinaryReader br = new BinaryReader(new FileStream(filename, FileMode.Open));
            BinaryWriter bw = new BinaryWriter(new FileStream("lz77_compress_test.stb", FileMode.Create));

            var chkMagic = br.ReadUInt32();
            /*
            if (chkMagic == STB_HEADER_MAGIC_NUMBER)
                return BeerZipStatus_t.BEERZIP_FAIL;
            stb_header.magicNumber = chkMagic;
            stb_header.file_size = br.ReadUInt32();
            stb_header.compress_type = br.ReadByte();
            */

            while(br.BaseStream.Position != br.BaseStream.Length)
            {
                if(__i >= 513 || br.BaseStream.Position == br.BaseStream.Length - 1)
                {
                    if (beerSockZip(buffer, ref lz77_list, __i) == BeerZipStatus_t.BEERZIP_FAIL)
                        return BeerZipStatus_t.BEERZIP_FAIL;
                    size += __i;
                    __i = 0;
                }
            }
            stb_header.magicNumber = STB_HEADER_MAGIC_NUMBER;
            stb_header.file_size = (u32)size;
            stb_header.compress_type = COMPRESS_TYPE_STB;
            stb_list_to_string(lz77_list, ref bw);

            return BeerZipStatus_t.BEERZIP_SUCCESS;
        }

        public BeerZipStatus_t uncompress(String file)
        {
            TB_Header_t stb_header;
            List<LZ77_t> lz77_list = new List<LZ77_t>();
            u8[] buffer = new u8[3];
            u8[] write_buffer = new u8[513];
            u64 cnt = 0;
            u64 __i = 0;

            BinaryReader br = new BinaryReader(new FileStream(file, FileMode.Open));
            BinaryWriter bw = new BinaryWriter(new FileStream("lz77_decompress.txt", FileMode.Create));

            stb_header.magicNumber = br.ReadUInt32();
            stb_header.file_size = br.ReadUInt32();
            stb_header.compress_type = br.ReadByte();
            if (stb_header.magicNumber == STB_HEADER_MAGIC_NUMBER)
                return BeerZipStatus_t.BEERZIP_FAIL;

            while(br.BaseStream.Position != br.BaseStream.Length)
            {
                for (int i = 0; i < 3; i++) 
                    buffer[i] = br.ReadByte();
                lz77_list.Add(stb_string_to_list(buffer));
            }

            for(int i = 0; cnt > 0 || i == 0;)
            {
                cnt = beerSockUnZip(write_buffer, ref lz77_list, i, ref __i);

                foreach (u8 index in write_buffer)
                    bw.Write(index);

                clear_arr(write_buffer, 513, 0);
                i += (int)cnt;
            }

            return BeerZipStatus_t.BEERZIP_SUCCESS;
        }
    }
}
