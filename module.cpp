#include "ship2.hpp"

void Module::swap(Ship* s) {
	unsigned int i;
	for (i=0; i<s->cargo.size(); i++) {
		if (s->type==MODULE_TYPE) {
			s->modi = cargo[i]; cargo.erase(i);
			cargo.push_back(this);
			return;
		}
	}
	// otherwise nothing needs to be done
}