#ifndef _MACAQUINHOS_

#include <iostream>
#include <vector>

using namespace std;

class Macaquinhos {

private:
  int macaco, par, impar, cocos;
  vector<int> pedrinhas;

public:
  Macaquinhos();

  void setMacaco(int macaco);
  void setPar(int par);
  void setImpar(int impar);
  void setCocos(int cocos);
  void setPedrinhas(int pedrinhas);
  int getMacaco();
  int getPar();
  int getImpar();
  int getCocos();
  void showPedrinhas(ostream &arquivo);
  void reduzCocos();
  int getPedrinhas();
  void aumentaCocos();
};

#endif