// 题目：970. 强整数（Powerful Integers）
// 思路：从小到大枚举 x 的幂 a 与 y 的幂 b，把满足 a + b <= bound 的和放进集合去重。
// 时间复杂度：O(log_x bound * log_y bound)，两重幂次枚举；空间复杂度：O(答案个数)，集合存储去重结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> powerfulIntegers(int x, int y, int bound) {  // x、y 是底数，bound 是上界，返回所有不超过 bound 的强整数
        unordered_set<int> ans;  // 集合：自动去重，最后统一转成数组
        for (int a = 1; a <= bound; a *= x) {  // 枚举 x 的幂 a，从 x^0 = 1 开始
            for (int b = 1; a + b <= bound; b *= y) {  // 枚举 y 的幂 b，同时保证 a + b 不超过上界
                ans.insert(a + b);  // a + b 就是一个强整数，插入集合去重
                if (y == 1) {  // y == 1 时 b 恒为 1，继续循环会死循环，必须跳出内层
                    break;  // 跳出内层循环
                }  // y 判断结束
            }  // 内层循环结束
            if (x == 1) {  // x == 1 时 a 恒为 1，同样要跳出外层避免死循环
                break;  // 跳出外层循环
            }  // x 判断结束
        }  // 外层循环结束
        return vector<int>(ans.begin(), ans.end());  // 集合转成数组返回（顺序不作要求）
    }  // 方法结束
};  // 题解类结束