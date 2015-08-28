#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>

#include <fastjet/ClusterSequence.hh>

using namespace std;
using namespace fastjet;

// read 4-momentum from input stream
istream& operator>>(istream &in, vector<PseudoJet>& p) {
  double px, py, pz, E;
  in >> px >> py >> pz >> E;
  if (in) p.emplace_back(px,py,pz,E);
  return in;
}

int main(int argc, char **argv)
{
  if (argc!=3) {
    cout << "Usage: " << argv[0] << " algorithm(kt,akt,ca) radius(0.4)" << endl;
    return 1;
  }

  // select algorithm
  JetDefinition jet_def(
    ( strcmp(argv[1],"kt")
      ? ( strcmp(argv[1],"antikt")
          ? ( strcmp(argv[1],"cambridge")
              ? throw "Undefined algorithm"
              : cambridge_algorithm )
          : antikt_algorithm )
      : kt_algorithm ),
    atof(argv[2])
  );
  
  // collect particles
  vector<PseudoJet> particles;
  while (cin >> particles) { }
  
  // define ClusterSequence
  ClusterSequence seq(particles, jet_def, false);
  
  // cluster jets
  vector<PseudoJet> jets = seq.inclusive_jets();
  
  // sort jets by pT
  sort( jets.begin(), jets.end(),
    [](const PseudoJet& i, const PseudoJet& j)
      { return i.pt() > j.pt(); }
  );

  // print jets' pT
  for (auto& jet : jets)
    cout << fixed << scientific << setprecision(8) << jet.pt() << endl;

  return 0;
}
