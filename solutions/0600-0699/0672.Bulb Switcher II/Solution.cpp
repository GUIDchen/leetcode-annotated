// 题目：672. 灯泡开关 Ⅱ（Bulb Switcher II）
// 思路：四种操作互不相同，最终状态只取决于每种操作被选用了奇数次还是偶数次；前 6 盏灯即可代表全部，故枚举 16 种组合并用位掩码去重。
// 时间复杂度：O(1)，固定枚举 16 种组合；空间复杂度：O(1)，集合最多保存 16 个状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int flipLights(int n, int presses) {  // n：灯泡个数；presses：必须按下的总次数
        n = min(n, 6);  // 每 6 盏灯一个周期，第 7 盏起的状态与前面重复，可截断
        vector<int> ops = {0b111111, 0b010101, 0b101010, 0b100100};  // 四种操作对前 6 盏灯的翻转掩码（位 5 是第 1 盏，位 0 是第 6 盏）
        unordered_set<int> vis;  // 收集可达的状态，自动去重
        for (int mask = 0; mask < 1 << 4; ++mask) {  // 枚举 4 种操作各自选或不选，共 16 种组合
            int cnt = __builtin_popcount(mask);  // 本组合实际按下的次数
            if (cnt > presses || cnt % 2 != presses % 2) continue;  // 次数超标，或剩余次数无法用成对的重复按键补齐，则该组合不可达
            int t = 0;  // 本组合得到的灯泡状态掩码
            for (int i = 0; i < 4; ++i) {  // 逐个检查第 i 种操作是否被选中
                if (mask >> i & 1) {  // 掩码第 i 位为 1 表示选用这种操作
                    t ^= ops[i];  // 异或等价于叠加一次翻转
                }
            }
            t &= (1 << 6) - 1;  // 只保留低 6 位，屏蔽无关高位
            t >>= (6 - n);  // 右移去掉后 6-n 盏灯，只留下真正要区分的前 n 盏灯
            vis.insert(t);  // 记录这个可达状态
        }
        return vis.size();  // 不同状态的数量即为答案
    }
};