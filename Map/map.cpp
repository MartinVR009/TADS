#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <list>
#include <stack>


using setIterator = std::set<std::string>::iterator;

using dictio = std::map<char, std::set<std::string>>;

using dictionaryIterator = std::map<char, std::set<std::string>>::iterator;

class Dictionary{
    private:
        dictio diccionario;
        dictio diccionario_reverso;

        bool dicc_ini = false;
        bool dicc_reverso_ini = false;


    public:
        Dictionary() {
            // Inicializa el mapa con letras de 'a' a 'z'
            for (char letra = 'a'; letra <= 'z'; letra++) {
                diccionario[letra];
                diccionario_reverso[letra];
            }
        }

        bool isPrefix(std::string word,std::string prefix){
            int tam = prefix.size();
            word = toLowerCase(word);
            if(word.size() >= tam){
                for(int i = 0; i < tam; i++){
                    if(word[i] == prefix[i]){
                        continue;
                    }else{
                        return false;
                    }
                }
                return true;
            }
            return false;
        }


        std::string toLowerCase(const std::string& str) {
            std::string result = str; // Crear una copia del string original

            // Convertir cada carácter a minúscula
            for (char& c : result) {
                c = std::tolower(c);
            }

            return result;
        }

        int getPoints(std::string word) {
            int puntaje = 0;
            // Recorre cada caracter de la palabra
            for (char c : word) {
                if (std::toupper(c) == 'E' ||
                    std::toupper(c) == 'A' ||
                    std::toupper(c) == 'I' ||
                    std::toupper(c) == 'O' ||
                    std::toupper(c) == 'N' ||
                    std::toupper(c) == 'R' ||
                    std::toupper(c) == 'T' ||
                    std::toupper(c) == 'L' ||
                    std::toupper(c) == 'S' ||
                    std::toupper(c) == 'U') {
                    puntaje += 1;
                } else if (std::toupper(c) == 'D' || std::toupper(c) == 'G') {
                    puntaje += 2;
                } else if (std::toupper(c) == 'B' ||
                        std::toupper(c) == 'C' ||
                        std::toupper(c) == 'M' ||
                        std::toupper(c) == 'P') {
                    puntaje += 3;
                } else if (std::toupper(c) == 'F' ||
                        std::toupper(c) == 'H' ||
                        std::toupper(c) == 'V' ||
                        std::toupper(c) == 'W' ||
                        std::toupper(c) == 'Y') {
                    puntaje += 4;
                } else if (std::toupper(c) == 'K') {
                    puntaje += 5;
                } else if (std::toupper(c) == 'J' || std::toupper(c) == 'X') {
                    puntaje += 8;
                } else if (std::toupper(c) == 'Q' || std::toupper(c) == 'Z') {
                    puntaje += 10;
                }
            }
            return puntaje;
        }

        std::string reverseWord(std::string expression) { 
            std::stack<char> rWord; 
            for (char c : expression) 
                rWord.push(c);          
            std::string reverse = "";      
            while (!rWord.empty()) {  
                reverse += rWord.top(); 
                                        
                rWord.pop();            
            }
            return reverse; 
        }

        bool verifyWord(std::string expression) { 
            for (char c : expression) { //Recorrer expression
                if (!std::isalpha(c)) { // Si no es alfanumerico
                    return false;
                }
            }
            return true; // Si la palabra es válida se retorna true
        }

        void InsertDiccionario(std::string word){
            diccionario[tolower(word[0])].insert(word);
        }

        void InsertDiccionarioReverso(std::string word){
            diccionario_reverso[tolower(word[0])].insert(reverseWord(word));
        }

        void iniciar_arbol(std::string filename){
            if(dicc_ini){
                std::cout<<"El árbol del diccionario ya ha sido inicializado\n";
                return;
            }

            std::ifstream file(filename);

            if(!file.is_open()){
                std::cout<<"No se pudo abrir el archivo: " << filename <<"\n";
                return;
            }

            std::string word;

            while(file >> word){
                if(verifyWord(word)){
                    InsertDiccionario(word);
                }
            }
            if(diccionario.size() != 0){
                std::cout<<"El árbol del diccionario se ha inicializado correctamente\n";
                dicc_ini = true;
            }
            file.close();
        }

        void iniciar_arbol_reverso(std::string filename){
            if(dicc_reverso_ini){
                std::cout<<"El árbol del diccionario ya ha sido inicializado\n";
                return;
            }
            std::ifstream file(filename);

            if(!file.is_open()){
                std::cout<<"El archivo: " << filename <<" no existe o no puede ser leído \n";
                return;
            }

            std::string word;

            while(file >> word){
                if(verifyWord(word)){
                    InsertDiccionarioReverso(word);
                }
            }
            if(diccionario_reverso.size() != 0) {
                std::cout<<"El árbol del diccionario inverso se ha inicializado correctamente\n";
                dicc_reverso_ini = true;
            }
            file.close();
        }


        void prefijos(std::string Prefix){
            std::cout<<"Palabras con prefijo: " << Prefix <<"\n";
            Prefix = toLowerCase(Prefix);
            setIterator it = diccionario[Prefix[0]].begin();
            for(; it != diccionario[Prefix[0]].end(); it++){
                if(isPrefix(*it, Prefix)){
                    std::cout<<*it << " , longitud: " << it->size() << ", puntaje: " << getPoints(*it) <<"\n";
                }
            }
            std::cout <<"\n-----------------------------------------\n";
        }


        void sufijos(std::string sufix){
            std::cout<<"Palabras con sufijo: " << sufix <<"\n";
            sufix = reverseWord(toLowerCase(sufix));
            setIterator it = diccionario_reverso[sufix[0]].begin();
            for(; it != diccionario_reverso[sufix[0]].end(); it++){
                if(isPrefix(*it, sufix)){
                    std::cout<<reverseWord(*it) << " , longitud: " << it->size() << ", puntaje: " << getPoints(*it) <<"\n";
                }
            }
            std::cout <<"\n-----------------------------------------\n";
        }
};

int main(){
    Dictionary system;

    system.iniciar_arbol("words.txt");
    system.iniciar_arbol_reverso("words.txt");
    system.prefijos("your");
    system.sufijos("ble");
    return 0;
}