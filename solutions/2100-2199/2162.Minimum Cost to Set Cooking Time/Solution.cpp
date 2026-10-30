// 题目：2162. 设置时间的最少代价（Minimum Cost to Set Cooking Time）
// 核心思路：把 targetSeconds 拆成「m 分 s 秒」与「m-1 分 s+60 秒」两种合法写法，分别按位模拟按键代价并取较小值。
// 时间复杂度：O(1)，固定只处理 4 位数字；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {  // startAt：起始指针位置；moveCost：移动一格代价；pushCost：按一次代价；targetSeconds：目标秒数
        int m = targetSeconds / 60, s = targetSeconds % 60;  // 常规拆法：得到分钟数与秒数
        return min(f(m, s, startAt, moveCost, pushCost), f(m - 1, s + 60, startAt, moveCost, pushCost));  // 两种合法拆分都模拟一遍，取较小代价
    }  // 方法结束

    int f(int m, int s, int prev, int moveCost, int pushCost) {  // 计算按顺序输入 m 分 s 秒所需代价；prev 是按键前指针所在位置
        if (m < 0 || m > 99 || s < 0 || s > 99) return INT_MAX;  // 分或秒超出两位范围，这种拆分非法，返回正无穷
        vector<int> arr = {m / 10, m % 10, s / 10, s % 10};  // 把分和秒各拆成两位数字，共 4 个待按的键
        int i = 0;  // i 指向第一个非零数字
        for (; i < 4 && arr[i] == 0; ++i)  // 跳过前导零：高位上的 0 不需要按
            ;  // 循环体为空，全部工作都在循环头里完成
        int t = 0;  // 累计按键代价
        for (; i < 4; ++i) {  // 从第一个非零位开始依次按键
            if (arr[i] != prev) t += moveCost;  // 指针不在目标数字上，先付出一次移动代价
            t += pushCost;  // 无论是否需要移动，都要按一次键
            prev = arr[i];  // 指针跟着移到刚按下的数字
        }  // 按键循环结束
        return t;  // 返回这种拆分的总代价
    }  // 方法结束
};  // 题解类定义结束