#ifndef VCZH_COMPILER_TINYMOELEXICALANALYZER
#define VCZH_COMPILER_TINYMOELEXICALANALYZER

#include "../TinymoeSTL.h"

namespace tinymoe
{
	namespace compiler
	{
		enum class CodeTokenType
		{
			Integer,
			Float,
			String,
			Identifier,

			Module,				// module declaration
			Using,				// import module declaration
			Phrase,				// phrase declaration
			Sentence,			// sentence declaration
			Block,				// block declaration
			Symbol,				// symbol declaration
			Type,				// type declaration

			CPS,				// continuation decoration
			Category,			// block category definition
			Expression,			// expression argument
			Argument,			// argument argument
			Assignable,			// assignable argument
			List,				// list

			End,				// end of an entity

			OpenBracket,		// (
			CloseBracket,		// )
			Comma,				// ,
			Colon,				// :
			Concat,				// &
			Add,				// +
			Sub,				// -
			Mul,				// *
			Div,				// /
			IntDiv,				// \ 
			Mod,				// %
			LT,					// <
			GT,					// >
			LE,					// <=
			GE,					// >=
			EQ,					// =
			NE,					// <>
			And,				// and
			Or,					// or
			Not,				// not

			Unknown,
		};

		struct CodeToken
		{
			typedef vector<CodeToken>				List;

			CodeTokenType					type = CodeTokenType::Unknown;
			int								row = -1;
			int								column = -1;
			string							value;
			int								codeIndex = -1;

			bool							IsNameFragmentToken();

			static string					EscapeString(string value);
			static string					UnescapeString(string str);
		};

		struct CodeError
		{
			typedef vector<CodeError>				List;

			CodeToken						position;
			string							message;
		};

		struct CodeLine
		{
			typedef shared_ptr<CodeLine>			Ptr;
			typedef vector<Ptr>						List;

			CodeToken::List					tokens;
		};

		struct CodeFile
		{
			typedef shared_ptr<CodeFile>			Ptr;
			typedef vector<Ptr>						List;

			CodeLine::List					lines;

			static CodeFile::Ptr			Parse(const string& code, int codeIndex, CodeError::List& errors);
		};

		class CodeFragment
		{
		public:
			CodeFragment();
			virtual ~CodeFragment();
		};

		class SymbolName : public CodeFragment
		{
		public:
			typedef shared_ptr<SymbolName>						Ptr;
			typedef vector<Ptr>									List;

			vector<CodeToken>									identifiers;

			string												GetName();
			string												GetComposedName();

			static bool											ConsumeToken(CodeToken::List::iterator& it, CodeToken::List::iterator end, CodeTokenType tokenType, const string& content, CodeToken ownerToken, CodeError::List& errors);
			static SymbolName::Ptr								ParseToEnd(CodeToken::List::iterator it, CodeToken::List::iterator end, const string& ownerName, CodeToken ownerToken, CodeError::List& errors);
			static SymbolName::Ptr								ParseToFarest(CodeToken::List::iterator& it, CodeToken::List::iterator end, const string& ownerName, CodeToken ownerToken, CodeError::List& errors);
		};
	}
}

#endif