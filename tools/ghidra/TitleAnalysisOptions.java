import ghidra.app.script.GhidraScript;
public class TitleAnalysisOptions extends GhidraScript {
 public void run() throws Exception {
  for(String key:getCurrentAnalysisOptionsAndValues(currentProgram).keySet()){
   if(key.equals("Decompiler Parameter ID") || key.equals("Decompiler Switch Analysis")){
    setAnalysisOption(currentProgram,key,"false");println("Disabled global "+key);
   }
  }
 }
}
