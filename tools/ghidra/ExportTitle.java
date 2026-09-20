// Export analysis evidence. These outputs are deliberately excluded from C match progress.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.nio.file.*;
import java.util.*;
public class ExportTitle extends GhidraScript {
 public void run() throws Exception {
  Path out=Paths.get(getScriptArgs()[0]);Files.createDirectories(out);
  long lo=getScriptArgs().length>1?Long.decode(getScriptArgs()[1]):0x369000;
  long hi=getScriptArgs().length>2?Long.decode(getScriptArgs()[2]):0x38a000;
  DecompInterface dc=new DecompInterface();dc.openProgram(currentProgram);
  ArrayList<String> index=new ArrayList<>(),calls=new ArrayList<>();
  index.add("address\tend\tsize\tname");calls.add("caller\tcallee");
  FunctionIterator it=currentProgram.getFunctionManager().getFunctions(true);
  while(it.hasNext() && !monitor.isCancelled()){
   Function f=it.next();long a=f.getEntryPoint().getOffset();
   index.add(String.format("%08X\t%08X\t%d\t%s",a,f.getBody().getMaxAddress().getOffset()+1,f.getBody().getNumAddresses(),f.getName()));
   if(a<lo || a>=hi)continue;
   String id=String.format("%08X",a);StringBuilder asm=new StringBuilder();
   InstructionIterator instructions=currentProgram.getListing().getInstructions(f.getBody(),true);
   while(instructions.hasNext()){Instruction i=instructions.next();asm.append(i.getAddress()).append(" ").append(i).append("\n");}
   Files.writeString(out.resolve(id+".s"),asm.toString());
   DecompileResults r=dc.decompileFunction(f,30,monitor);
   if(r.decompileCompleted())Files.writeString(out.resolve(id+".c"),"/* AUTOMATIC ANALYSIS: NOT MATCHING SOURCE */\n"+r.getDecompiledFunction().getC());
   for(Function c:f.getCalledFunctions(monitor))calls.add(id+"\t"+c.getEntryPoint());
  }
  Files.write(out.resolve("functions.tsv"),index);Files.write(out.resolve("calls.tsv"),calls);
  dc.dispose();println("Export complete: "+out);
 }
}
