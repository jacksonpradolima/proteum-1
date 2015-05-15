package trebam;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Map;

public class Proteum{

    public Proteum() {
    }
    
    /**
     * Gerar Script 1
     */
    public void gerarScript1(String programa, File diretorioProteum, File diretorioCasosTeste, int qtdCasosTeste){
        ManipularArquivo manipulador = new ManipularArquivo();
        File f = new File(diretorioProteum.toString()+"/script_prot1.sh");
        ArrayList arr = new ArrayList();
        arr.add("cd "+diretorioProteum.toString()+"/");
        int tamanho = programa.length();
        arr.add("gcc -o exe "+programa+" -lm");
        arr.add("test-new -research -S "+programa.substring(0, tamanho-2) +" -E exe -C \"gcc -o exe "+programa+" -lm\" testSection");
        arr.add("muta-gen -all 100 testSection");
        arr.add("tcase -poke -E exe -DD "+diretorioCasosTeste.toString()+"/ -f 1 -t "+qtdCasosTeste+" testSection");
        arr.add("tcase -i testSection");
        arr.add("report -tcase testSection");
        manipulador.gravaComandoScript(f, arr);
    }
    
    /**
     * Executando script 1 - proteum
     */
    public void executarProteumScript1(File diretorioProteum){
        try{
            String [] args = new String [3];
            args [0] ="chmod";
            args [1] ="777";
            args [2] =diretorioProteum.toString()+"/script_prot1.sh";
            Runtime.getRuntime().exec(args);
            
            
            ProcessBuilder pBuilder = new ProcessBuilder("/bin/sh", diretorioProteum.toString()+"/script_prot1.sh"); 
            Map<String, String> env1 = pBuilder.environment();
            env1.put("PATH", env1.get("PATH") + ":/usr/local/proteum1.4.1/LINUX/bin");
            env1.put("PROTEUM14HOME","/usr/local/proteum1.4.1/LINUX/bin");
            pBuilder.directory(diretorioProteum);
            pBuilder.redirectErrorStream(true);  
            
            String line = null;  
            
            try {  
                Process p = pBuilder.start();  
                p.waitFor();  
                BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));  
   
                while((line = reader.readLine()) != null)  
                {  
                    System.out.println(line);  
                }  
            } catch (Exception ex) {  
                ex.printStackTrace();  
            }
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }
    
    /**
     * Gerar Script 2
     */
    public void gerarScript2(File diretorioProteum, int nroCasoTeste, int nroMutantes){
        ManipularArquivo manipulador = new ManipularArquivo();
        File f = new File(diretorioProteum.toString()+"/script_prot2.sh");
        ArrayList arr = new ArrayList();
        arr.add("cd "+diretorioProteum.toString()+"/");
        arr.add("tcase -e -f "+nroCasoTeste+" -t "+nroCasoTeste+" testSection");
        arr.add("exemuta -exec testSection");
        arr.add("(muta -l -f 0 -t "+nroMutantes+" testSection) > mutantes.txt");
        arr.add("report -tcase -L 510 testSection");
        manipulador.gravaComandoScript(f, arr);
    }
    
    /**
     * Executando script 2 - proteum
     */
    public void executarProteumScript2(File diretorioProteum){
        try{
            String [] args = new String [3];
            args [0] ="chmod";
            args [1] ="777";
            args [2] =diretorioProteum.toString()+"/script_prot2.sh";
            Runtime.getRuntime().exec(args);
            
            ProcessBuilder pBuilder = new ProcessBuilder("/bin/sh", diretorioProteum.toString()+"/script_prot2.sh"); 
            Map<String, String> env1 = pBuilder.environment();
            env1.put("PATH", env1.get("PATH") + ":/usr/local/proteum1.4.1/LINUX/bin");
            env1.put("PROTEUM14HOME","/usr/local/proteum1.4.1/LINUX/bin");
            pBuilder.directory(diretorioProteum);
            pBuilder.redirectErrorStream(true);  
            
            String line = null;  
            
            try {  
                Process p = pBuilder.start();  
                p.waitFor();  
                BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));  
   
                while((line = reader.readLine()) != null)  
                {  
                    System.out.println(line);  
                }  
            } catch (Exception ex) {  
                ex.printStackTrace();  
            }
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }
    
    public int getNroMutantesGerados(File diretorioProteum){
        try {
            BufferedReader in = new BufferedReader(new FileReader(new File(diretorioProteum.toString()+"/testSection.lst")));
            String str="";
            for (int i=0; i<8; i++) {
                str = in.readLine();
            }
            str = str.substring(20);
            in.close();
            return Integer.parseInt(str);
        } catch (IOException e) {
            return 0;
        }
    }
    
    public ArrayList capturarResultados(File diretorioProteum){
        ArrayList resultados = new ArrayList();
        try {
            BufferedReader in = new BufferedReader(new FileReader(new File(diretorioProteum.toString()+"/mutantes.txt")));
            String str="";
            int nroMut=0;
            while ((str = in.readLine()) != null) {
                if(str.contains("MUTANT #")){
                    str = str.substring(9);
                    nroMut = Integer.parseInt(str);
                    str = in.readLine();
                    Mutante mt = new Mutante();
                    mt.setId(nroMut);
                    if(str.contains("Dead")){
                        mt.setStatus("DEAD");
                    } else if (str.contains("Alive")){
                        mt.setStatus("ALIVE");
                    } else if (str.contains("Anomalous")){
                        mt.setStatus("ANOMALOUS");
                    }
                    int j=0;
                    while(j<8){
                        str = in.readLine();
                        if(str.contains("Operator")){
                            mt.setOperador(this.getOperador(str));
                        }
                        j++;
                    }
                    resultados.add(mt);
                }
            }
            in.close();
            return resultados;
        } catch (IOException e) {
            return resultados;
        }
    }
    
    private String getOperador(String str){
        char c ='0';
        for(int i=0; i<str.length(); i++){
            c = str.charAt(i);
            if(c == '('){
                return str.substring(i+1, str.length()-1);
            }
        }
        return "";
    }
}