class Solution {
public:
     static int reverse(int x) {
        int result = 0;
        int max = INT32_MAX / 10;
        int min = INT32_MIN / 10;
        while(x != 0){
            int less = x % 10;
            x /= 10;

            //上限
            if(result > max || (result == max && less > 7))
                return 0;

            //下限
            if(result < min || (result == min && less < -8))
                return 0;

            result = result * 10 + less;
        }
        return result;
    }
};
