#ifndef FACTORY_HPP
#define FACTORY_HPP

class Factory: public Interactive {
	public:
		// incoming ships with their configurations preset
		std::vector<Ship*> queue;

		explicit Factory(): Interactive() {
		}
		virtual void typeinit2() {
            types.push_back(Typenum::FACTORY);
            typeinit3();
        }
        virtual void typeinit3() {}

		virtual void dimsinit() { w=160; h=80; }
		// imginit() sets several sub-images, the hitbox is for the platform

		void teaminit(Config*);
};

#endif
