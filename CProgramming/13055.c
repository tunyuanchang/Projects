#include <stdio.h>
#include "function.h"

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int type, p1, q1, p2, q2;
		scanf("%d %d/%d %d/%d", &type, &p1, &q1, &p2, &q2);
		Fraction f1 = CreateFrac(p1, q1), f2 = CreateFrac(p2, q2), ans;
		switch (type) {
			case 0:
				ans = Add(f1, f2);
				printf("%lld/%lld\n", ans.numerator, ans.denominator);
				break;
			case 1:
				ans = Compare(f1, f2) ? Sub(f1, f2) : Sub(f2, f1);
				printf("%lld/%lld\n", ans.numerator, ans.denominator);
				break;
			case 2:
				ans = Mul(f1, f2);
				printf("%lld/%lld\n", ans.numerator, ans.denominator);
				break;
			case 3:
				ans = Div(f1, f2);
				printf("%lld/%lld\n", ans.numerator, ans.denominator);
				break;
			case 4:
				Reduction(&f1), Reduction(&f2);
				printf("%lld/%lld %lld/%lld\n", f1.numerator, f1.denominator, f2.numerator, f2.denominator);
				break;
		}
	}
}
