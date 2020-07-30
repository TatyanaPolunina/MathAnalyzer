#include "mathAnalyzer.h"

MathAnalyzer::MathAnalyzer(const std::string& input_expr)
: string_parsed(false)
{
	
}

bool MathAnalyzer::is_string_correct() const
{
	return string_parsed;
}