using System;
class Program
{
    static void Main(string[] args)
    {
        byte[] testCode = { 
            // set reg
            0x00, 0xff, 0xFA, 0x69,
            // useless
            0x5D, 0x33,
            // move reg
            0x01, 0xFF, 0xDD,
            // useless
            0xA
        };
        var lexer = new BytecodeLexer(testCode);
        lexer.Run();

        foreach (BytecodeCommand c in lexer.collectedCommands)
        {
            Console.WriteLine(c.command);

            foreach (byte a in c.arguments) {
                Console.WriteLine(a);
            }

            Console.WriteLine("~~~~~~~~~~~~");
        }
    }
}