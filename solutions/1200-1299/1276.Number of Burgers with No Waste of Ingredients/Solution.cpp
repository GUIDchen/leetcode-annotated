class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {  // tomatoSlices：番茄片数；cheeseSlices：奶酪片数
        int k = 4 * cheeseSlices - tomatoSlices;  // 由 4x+2y=tomato、x+y=cheese 推出 2y = 4·cheese - tomato
        int y = k / 2;  // 解出小汉堡个数 y
        int x = cheeseSlices - y;  // 巨无霸个数 x = 奶酪片数 - 小汉堡个数
        return k % 2 || x < 0 || y < 0 ? vector<int>{} : vector<int>{x, y};  // 余数非 0 说明不是整数解，x 或 y 为负说明无解；否则返回 {x, y}
    }  // numOfBurgers 方法结束
};  // Solution 类定义结束