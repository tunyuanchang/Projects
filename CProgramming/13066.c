#include <stdio.h>
#include "function.h"

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int type, p1, q1, p2, q2;
		scanf("%d %d%di %d%di", &type, &p1, &q1, &p2, &q2);
		Complex f1 = CreateComplex(p1, q1), f2 = CreateComplex(p2, q2), ans;
		switch (type) {
			case 0: 
				ans = Add(f1, f2);
				if(ans.imag >= 0) printf("%lld+%lldi\n", ans.real, ans.imag);
				else printf("%lld%lldi\n", ans.real, ans.imag);
				break;
			case 1: 
				ans = Sub(f1, f2);
				if(ans.imag >= 0) printf("%lld+%lldi\n", ans.real, ans.imag);
				else printf("%lld%lldi\n", ans.real, ans.imag);
				break;
			case 2: 
				ans = Mul(f1, f2);
				if(ans.imag >= 0) printf("%lld+%lldi\n", ans.real, ans.imag);
				else printf("%lld%lldi\n", ans.real, ans.imag);
				break;
			case 3: 
				Compare(&f1, &f2);
				if(f1.imag >= 0) printf("%lld+%lldi\n", f1.real, f1.imag);
				else printf("%lld%lldi\n", f1.real, f1.imag);
				break;
		}
	}
}
