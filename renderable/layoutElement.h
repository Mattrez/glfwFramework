struct LayoutElement
{
	/* You canno't make a LayoutElement object without having data for it */
	LayoutElement(unsigned int count, unsigned int type, unsigned int normalized) :
		count(count),
		type(type),
		normalized(normalized)
{ } 
public:
	const unsigned int count;
	const unsigned int type;
	const unsigned int normalized;
};
