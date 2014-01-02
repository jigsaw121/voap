class WallAmbassador: public Interactive() {
	// haha dese names man
	// basically an interface to handle wall collisions
	// -> collide with this instead of the image layers directly
	// an inherited version could destroy the walls on collision too
	// quadtrees and shiz whenever needed, even a couple of huge layers run smoothly right now
	public:
		explicit WallAmbassador(): Interactive() {}
}