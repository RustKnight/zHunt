#pragma once



//	N-0, NE-1, E-2, SE-3, S-4, SW-5, W-6, NW-7

class TurnAround {
public:

	void update(float in_eTime, bool ready) {
		eTime = in_eTime;
		finishedShooting = ready;
	}

	void setCurrent(int current) {
		lastTarget = currentTarget;
		currentTarget = current;
		facing = lastTarget;
	}

	bool complete() {
		if ((int)facing == currentTarget)
			return true;


		fastestTurn();
		if (finishedShooting)
			startTurning();
		return false;
	}

	void startTurning() {

		if (turnRight) {
			facing += roateSpeed * eTime;
			if (facing > 7.9999f)
				facing = 0;
		}
		else {
			facing -= roateSpeed * eTime;
			if (facing < 0)
				facing = 7;
		}
	}


	void fastestTurn() {

		int inc = lastTarget;
		int dec = lastTarget;

		while ((inc != currentTarget) && (dec != currentTarget)) {
			inc++;
			dec--;

			if (inc > 7)
				inc = 0;
			if (dec < 0)
				dec = 7;
		}

		if (inc == currentTarget)
			turnRight = true;
		else if (dec == currentTarget)
			turnRight = false;
	}

	int getFacing() {
		return facing;
	}

private:
	int lastTarget = 0;
	int currentTarget = 0;
	float facing = 0;
	float roateSpeed = 3.0f;
	float eTime;
	bool turnRight = true;
	bool finishedShooting = true;
};
