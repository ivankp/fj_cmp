#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>
#include <cstdio>
#include <sys/time.h>

#include <TRandom3.h>

using namespace std;

string exec(const char* cmd) {
  FILE* pipe = popen(cmd, "r");
  if (!pipe) return "ERROR";
  char buffer[128];
  std::string result = "";
  while(!feof(pipe)) {
  	if(fgets(buffer, 128, pipe) != NULL)
  		result += buffer;
  }
  pclose(pipe);
  return result;
}

int main(int argc, char **argv)
{
  if (argc!=3) {
    cout << "Usage: " << argv[0] << " algorithm(kt,akt,ca) radius(0.4)" << endl;
    return 1;
  }

  timeval tv;
  gettimeofday(&tv, nullptr);
  
  TRandom3 r(tv.tv_usec);
  array<double,8> p;
  for (int i=0; i<8; ++i) p[i] = r.Rndm();
  
  stringstream cmd1;
  cmd1 << "echo";
  for (int i=0; i<8; ++i) cmd1 << ' ' << p[i];
  cmd1 << " | ../fj/fj " << argv[1] << ' ' << argv[2];
  
  stringstream cmd2;
  cmd2 << "java -classpath ../n2jet_java test " << argv[1] << ' ' << argv[2];
  for (int i=0; i<8; ++i) cmd2 << ' ' << p[i];
  
  string out1 = exec(cmd1.str().c_str());
  string out2 = exec(cmd2.str().c_str());
  
  for (size_t c = out1.find('#'); c!=string::npos; c = out1.find('#')) {
    out1 = out1.substr(out1.find('\n')+1);
  }
  
  cout << fixed << scientific << setprecision(8);
  
  if (out1 != out2) {
    for (int i=0; i<4; ++i) cout << p[i] << ' ';
    cout << endl;
    for (int i=4; i<8; ++i) cout << p[i] << ' ';
    cout << endl;
    cout << endl;
    cout << out1 << endl;
    cout << out2 << endl;
  }

  return 0;
}
