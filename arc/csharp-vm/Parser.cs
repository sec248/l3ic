using System.Collections.Generic;

enum BytecodeOpcode
{
    SetRegister,
    SwapRegister,
    SetLabel
}

struct BytecodeCommand
{
    public BytecodeOpcode command;
    public byte[] arguments;
}

struct JumpInstruction
{
    public uint jumpId;
    public ulong sourceIdx;
}

class BytecodeLexer
{
    private BytecodeOpcode? collected;
    private byte collectLengthToStop;
    private ulong idx;
    private byte[] source;
    private List<byte> collectedArgs;
    public List<JumpInstruction> jumpTable;
    public List<BytecodeCommand> collectedCommands;

    public BytecodeLexer(byte[] givenSource)
    {
        source = givenSource;
        idx = 0;
        collectedArgs = new List<byte>();
        collectLengthToStop = 0; 
        collectedCommands = new List<BytecodeCommand>();
        jumpTable = new List<JumpInstruction>();
        collected = null;
    }

    public void Run()
    {
        foreach (byte code in source)
        {
            Parse(code);
            idx++;
        }
    }

    private void Parse(byte code)
    {
        if (collected == null)
        {
            collected = (BytecodeOpcode)code;

            switch (collected)
            {
                case BytecodeOpcode.SetRegister:
                    collectLengthToStop = 3;
                    break;
                case BytecodeOpcode.SwapRegister:
                    collectLengthToStop = 2;
                    break;
                default:
                    collected = null;
                    break;
            }
        }
        else
        {
            AddToCollector(code);
        }
    }

    private void AddToCollector(byte given)
    {
        collectedArgs.Add(given);

        if (collectedArgs.Count == collectLengthToStop)
        {
            if (collected == BytecodeOpcode.SetLabel) {
                var jumpIns = new JumpInstruction();

                if (collectedCommands.Count == 0)
                    jumpIns.sourceIdx = 0;
                else
                    jumpIns.sourceIdx = collectedArgs.Count - 1;

                collectedCommands.Add(bytecodeCommand);

                collected = null;
                collectedArgs.Clear();
                collectLengthToStop = 0;
            } else {
                var bytecodeCommand = new BytecodeCommand();
                bytecodeCommand.arguments = collectedArgs.ToArray();
                bytecodeCommand.command = collected.Value;

                collectedCommands.Add(bytecodeCommand);

                collected = null;
                collectedArgs.Clear();
                collectLengthToStop = 0;
            }
        }
    }
}