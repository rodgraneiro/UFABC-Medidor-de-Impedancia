import processing.serial.*;
Serial portMaster;
//Serial portSlave;
PrintWriter output; 
float xanterior=0;
float x =100;
float wanterior=0;
float w =100;
float yanterior=0;
float y=0;
float zanterior=0;
float z=0;
String k;
int valor=0;
int master=0;
int slave=0;

void setup(){
  size(900,400);
  background(0);
   //String portMaster = Serial.list()[1];
  //port= new Serial(this,portName,9600);
   portMaster = new Serial(this, "COM3", 9600);
   //portSlave= new Serial(this, "COM7", 9600);
                                                                               
    output = createWriter( "MED10_0_1R_sem_Capacitor_2021set27.txt" );
}
void draw(){

  String tensao = portMaster.readStringUntil('\n');
   portMaster.write(66); // letra "B"
   delay(10);                                
  if(tensao!=null){
    y=float(tensao);
    valor = valor + 1;
    print(master);
    print(" ; ");                                                     
    print(y);
    println(" ; ");
    output.print(master); 
    output.print(" ; ");
    output.print(y);
    output.print(" ; ");
    if(valor == 2){
        output.println("");
        valor = 0;
        master = master + 1;
    }
        yanterior=y;
        textSize(24);
        textAlign(CENTER);
         text("Medição Nr:",120,140);
         fill(0);
         rect(190,110,150,40);
         
         fill(255);
         text(master-1,250,140);
     
  }
   
}
  
  

void mouseClicked() {
   xanterior=100;
      x=100;
      wanterior=100;
      w=100;
      yanterior=400;
      y=400;
      zanterior=400;
      z=400;
      master = 0;
      slave = 0;
      clear();
       rect(100,200,1500,400);
  }
  
  void keyPressed() { //Se alguma tecla for pressionada
  output.flush(); // Termina de escrever os dados pro arquivo
  output.close(); // Fecha o arquivo
  exit(); // Para o programa
}
