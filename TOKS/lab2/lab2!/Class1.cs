using System;
using System.Collections.Generic;
using System.Text;

namespace Lab2
{
    class ByteStuffing
    {
        private static byte F_END_SYMBOL = 0x7E;
        private static byte T_END_SYMBOL = 0x7D;
        private static byte F_ESC_SYMBOL = 0x5E;
        private static byte T_ESC_SYMBOL = 0x5D;

        public static byte[] encode(byte[] bytes)
        {
            List<byte> list = new List<byte>();

            for (int i = 0; i < bytes.Length; i++)
            {
                list.Add(bytes[i]);
            }

            list.Insert(0, F_END_SYMBOL);

            for (int i = 1; i < list.Count; i++)
            {
                if (list[i] == T_END_SYMBOL)
                {
                    list.Insert(i + 1, T_ESC_SYMBOL);
                    //i++;
                }
                else if (list[i] == F_END_SYMBOL)
                {
                    list[i] = T_END_SYMBOL;
                    list.Insert(i + 1, F_ESC_SYMBOL);
                    //i++;
                }
            }
            byte[] returnBytes = new byte[list.Count];

            return returnBytes = list.ToArray();
        }

        public static byte[] decode(byte[] bytes)
        {
            List<byte> list = new List<byte>();

            for (int i = 0; i < bytes.Length; i++)
            {
                list.Add(bytes[i]);
            }

            list.RemoveAt(0);

            for (int i = 1; i < list.Count; i++)
            {
                if (list[i] == T_END_SYMBOL)
                {
                    if (list[i + 1] == F_ESC_SYMBOL)
                    {
                        list[i] = F_END_SYMBOL;
                        list.RemoveAt(i + 1);
                    }
                }
                else if (list[i] == T_END_SYMBOL)
                {
                    list.RemoveAt(i + 1);
                }
            }
            byte[] returnBytes = new byte[list.Count];

            return returnBytes = list.ToArray();
        }
    }
}
