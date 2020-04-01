enum lines{NOLINE, SINGLELINE, DOUBLELINE};
enum modes{NOMODE, INT_FLOAT, INT_INT_INT};
enum parameters{THERMAL_CONDUCTIVITY, HEAT_SOURCE};
enum sizes{NODES, ELEMENTS, DIRICHLET, NEUMANN};

class item{//por que protected y no prived porque cuando hagamos que herede de una clase item en ese caso va a poder acceder a todo lo que este dentro de protected si fuera prived no habria forma
protected:
    int id;
    float x;
    int node1;
    int node2;
    float value;

public:
    //Getters para los atributos
        int getId() const {
            return id;
        }

        float getX() const { 
            return x;
        }

        int getNode1() const {
            return node1;
        }

        int getNode2() const {
            return node2;
        }

        float getValue() const {
            return value;
        }      

       //metodos abstractos virtual hace sinonimo de abstrac
       virtual void setIntFloat(int n, float r)=0;
       //con igualar a 0 le estamos diciendo que el metodo ha sido definido pero no implementado 
       virtual void setIntInt(int n1, int n2, int n3)=0; 
};

//---------------CLASE NODO------------------------------
class node: public item{   
public:
    void setIntFloat(int identificador, float x_coordinate){
        id = identificador;
        x=x_coordinate;
    }

    void setIntInt(int n1, int n2, int n3){

    } 
};

//------------------CLASE ELEMENTO------------------------
class element: public item{
public:
     void setIntFloat(int identificador, float x_coordinate){
       
    }

    void setIntInt(int identificador, int n1, int n2){
        id=identificador;
        node1=n1;
        node2=n2;
    }  

}; 

//-------------------CLASE CONDITION-----------------------
class condition: public item{
public:
    void setIntFloat(int node_to_apply , float prescribed_value){
        node1 = node_to_apply;
        value= prescribed_value;
    }

    void setIntInt(int n1, int n2, int n3){

    }

};

//------------------CLASE MESH (NO HEREDA)-----------------
//Clase que representa la malla del problema

class mesh{
        /* Si la longitud L es constante */
        float parameters[3];// Para este caso, los valores de l, k y Q
       // float parameters[2];
        int sizes[4]; //La cantidad de nodos, elementos, condiciones de dirichlet y neumann
        node *node_list; //Arreglo de nodos
        element *element_list; //Arreglo de elementos
        condition *dirichlet_list; //Arreglo de condiciones de Dirichlet
        condition *neumann_list; //Arreglo de condiciones de Neumann
    public:
        /* Metodo para instanciar el arreglo de parametros, almacenando los
         k y Q, en ese orden */
        
        //Ya no recibimos la longitud aqui
        void setParameters(float k,float Q){
            parameters[THERMAL_CONDUCTIVITY]=k;
            parameters[HEAT_SOURCE]=Q;
        }

        //Metodo para instanciar el arreglo de cantidades, almacenando la cantidad
        //de nodos, de elementos, y de condiciones (de Dirichlet y de Neumann)
        void setSizes(int nnodes,int neltos,int ndirich,int nneu){
            sizes[NODES] = nnodes;
            sizes[ELEMENTS] = neltos;
            sizes[DIRICHLET] = ndirich;
            sizes[NEUMANN] = nneu;
        }

        //Metodo para obtener una cantidad en particular
        int getSize(int s){
            return sizes[s];
        }

        //Metodo para obtener un parametro en particular
        float getParameter(int p){
            return parameters[p];
        }

        
         //Metodo para instanciar los cuatro atributos arreglo, usando
        //las cantidades definidas
        void createData(){
            node_list = new node[sizes[NODES]];
            element_list = new element[sizes[ELEMENTS]];
            dirichlet_list = new condition[sizes[DIRICHLET]];
            neumann_list = new condition[sizes[NEUMANN]];
        }

        //Getters para los atributos arreglo
        node* getNodes(){
            return node_list;
        }
        element* getElements(){
            return element_list;
        }
        condition* getDirichlet(){
            return dirichlet_list;
        }
        condition* getNeumann(){
            return neumann_list;
        }

        //Metodo para obtener un nodo en particular
        node getNode(int i){
            return node_list[i];
        }

        //Metodo para obtener un elemento en particular
        element getElement(int i){
            return element_list[i];
        }

        //Metodo para obtener una condicion en particular
        //(ya sea de Dirichlet o de Neumann)
        condition getCondition(int i, int type){
            if(type == DIRICHLET) return dirichlet_list[i];
            else return neumann_list[i];
        } 
    };