
template <class inVec>
std::vector<void*> find_locs(HANDLE process, inVec pattern, int offset) {

	std::vector<void*> outVec;
	unsigned char* p = NULL;
	MEMORY_BASIC_INFORMATION info;

	for (p = NULL;
		VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info);
		p += info.RegionSize)
	{
		std::vector<char> buffer;
		std::vector<char>::iterator pos;

		if (info.State == MEM_COMMIT &&
			(info.Type == MEM_MAPPED || info.Type == MEM_PRIVATE))
		{
			SIZE_T bytes_read;
			buffer.resize(info.RegionSize);
			ReadProcessMemory(process, p, &buffer[0], info.RegionSize, &bytes_read);
			buffer.resize(bytes_read);
			for (pos = buffer.begin();
				buffer.end() != (pos = std::search(pos, buffer.end(), pattern.begin(), pattern.end()));
				++pos)
			{
				outVec.push_back(p + (pos - buffer.begin() + offset));
			}
		}

	}
	return outVec;
}