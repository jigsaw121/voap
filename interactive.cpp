bool Interactive::collide(Interactive* obj) {
	// optimizations in searching for types
	return !( (y+w < obj->y) ||
			  (y > obj->y+obj->w) ||
			  (x > obj->x+obj->w) ||
			  (x+w < obj->x) );
}
std::vector<Interactive*> Interactive::find(ftype) {
	std::vector<Interactive*> out;
	
	// sort gm's objects so all objects of the same type are next to each other
	// (jump straight to where the wanted type is, cancel on first that isn't of the same type)
	int i; Interactive* obj;
	for (i=0; i<gm.objects.size(); i++) {
		obj = gm.objects.at(i);
		if (obj->type != ftype) continue;
		if (abs(obj->x-x)>obj->w+w || abs(obj->y-y)>obj->h+h) continue;
		out.push_back(obj);
	}
	
	return out;
}
std::vector<Interactive*> mergevectors(std::vector<Interactive*> a, std::vector<Interactive*> b) {
	std::vector<Interactive*> out;
	out.reserve(a.size() + b.size()); 
	out.insert(out.end(), a.begin(), a.end());
	out.insert(out.end(), b.begin(), b.end());
	return out;
}
std::vector<Interactive*> Interactive::collidetype(int type) {
	int i=0; Interactive* obj;
	std::vector<Interactive*> found = find(types.at(i));
	while (i<found.size()) {
		obj = found.at(i);
		if (!collide(obj)) found.erase(i);
		else i++;
	}
	return found;
}
std::vector<Interactive*> Interactive::collidetypes(std::vector<int> types) {
	int i; std::vector<Interactive*> colls;
	for (i=0; i<types.size(); i++) {
		colls = mergevectors(colls, collidetype(types.at(i)));
	}
	return colls;
}