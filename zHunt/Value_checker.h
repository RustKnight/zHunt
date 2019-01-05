#pragma once



class Value_checker {

public:
	bool value_changed(int value) {

		new_value = value;

		if (new_value == old_value || old_value == 123456789) {
			old_value = new_value;
			return false;
		}

		old_value = new_value;

		return true;
	}

private:
	int new_value = 123456789;
	int old_value = 123456789;
};
