#include <string>

class MathAnalyzer
{
	public:
		MathAnalyzer(const std::string& parse_string);
		bool is_string_correct() const;
	private:
		bool string_parsed;
};
