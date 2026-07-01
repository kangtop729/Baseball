#include <stdexcept>
#include <string>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	Baseball(const string& answer) {
		validateInput(answer);
		this->answer = answer;
	}

	GuessResult guess(const string& input) {
		try {
			validateInput(input);
			return calculateResult(input);
		} catch (...) {
			throw;
		}
	}

private:
	string answer;

	void validateInput(const string& input) {
		if (input.length() != 3)
			throw length_error("Input must be exactly three digits.");
		for (int i = 0; i < 3; i++) {
			if (!isdigit(input[i]))
				throw invalid_argument("Input must contain only digits.");
		}
	}

	bool isStrike(int pos, const string& input) {
		return input[pos] == answer[pos];
	}

	bool isBall(int pos, const string& input) {
		for (int j = 0; j < 3; j++) {
			if (j != pos && input[pos] == answer[j])
				return true;
		}
		return false;
	}

	GuessResult calculateResult(const string& input) {
		int strikes = 0, balls = 0;
		for (int i = 0; i < 3; i++) {
			if (isStrike(i, input))
				strikes++;
			else if (isBall(i, input))
				balls++;
		}
		return GuessResult{ strikes == 3, strikes, balls };
	}
};
