#include "Backtrack.h";
#include "backtrackflex.h";

using std::cin;
using std::cout;
using std::endl;

int main() {
	Backtrack b(14);

	//vector<int> getallen(8);
	//for (int i = 0; i < 8; i++) {
	//	getallen[i] = i;
	//	cout << i << ":" << getallen[i] << endl;
	//}

	b.losOp(false);

	/*cout << b.controleerSomVierOpeenvolgende(4) << endl;
	cout << b.controleerDrieOpeenvolgende(8) << endl;
	cout << b.controleerVerschillendVanZesde(1) << endl;*/
	return 0;
}