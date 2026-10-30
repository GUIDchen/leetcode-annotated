// 题目：2105. 给植物浇水 II（Watering Plants II）
// 思路：Alice 从左、Bob 从右相向浇水，各自记录壶中剩余水量；浇水前若不够就补满并计数，相遇时中间那株由剩余水量多的人来浇。
// 时间复杂度：O(n)，两个指针总共只走一遍数组；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {  // plants：每株植物需要的水量；capacityA/capacityB：两人水壶的容量
        int a = capacityA, b = capacityB;  // a、b 分别记录 Alice、Bob 当前壶里剩的水，初始都是满壶
        int ans = 0;  // ans 统计补水的总次数
        int i = 0, j = plants.size() - 1;  // i 从最左、j 从最右出发，两人相向而行
        for (; i < j; ++i, --j) {  // 只要两人还没相遇，就同步处理左右两端各一株
            if (a < plants[i]) {  // Alice 剩下的水不够浇第 i 株
                ++ans;  // 记一次补水
                a = capacityA;  // 把 Alice 的水壶补满
            }  // 这个 if 分支结束
            a -= plants[i];  // 浇完第 i 株，从壶里扣掉对应水量
            if (b < plants[j]) {  // Bob 剩下的水不够浇第 j 株
                ++ans;  // 记一次补水
                b = capacityB;  // 把 Bob 的水壶补满
            }  // 这个 if 分支结束
            b -= plants[j];  // 浇完第 j 株，从壶里扣掉对应水量
        }  // 两端循环结束，此时 i 与 j 相遇或交错
        ans += i == j && max(a, b) < plants[i];  // 若还剩中间一株（i == j），由剩余水量多的人去浇；水不够就再补一次（布尔值参与加法）
        return ans;  // 返回最少的补水次数
    }  // 方法结束
};  // 题解类结束