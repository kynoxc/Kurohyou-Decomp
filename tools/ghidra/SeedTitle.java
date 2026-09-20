import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
import java.util.*;
public class SeedTitle extends GhidraScript {
 public void run() throws Exception {
  List<String> lines=Files.readAllLines(Paths.get(getScriptArgs()[0]));
  for(int n=0;n<lines.size()-1;n++){
   long lo=Long.parseLong(lines.get(n).split("\t")[0],16);
   long hi=Long.parseLong(lines.get(n+1).split("\t")[0],16);
   if(hi-lo>16384)continue;
   Address start=toAddr(lo),end=toAddr(hi-1);
   // Linear disassembly makes switch arms available without global decompiler analysis.
   for(long at=lo;at<hi;at+=4)if(getInstructionAt(toAddr(at))==null)disassemble(toAddr(at));
   Function f=getFunctionAt(start);
   if(f==null)currentProgram.getFunctionManager().createFunction("FUN_"+String.format("%08X",lo),start,new AddressSet(start,end),SourceType.ANALYSIS);
   else if(getScriptArgs().length>1 && getScriptArgs()[1].equals("resize"))f.setBody(new AddressSet(start,end));
  }
  println("Seeded title candidates (boundaries require audit against callers and returns)");
 }
}
