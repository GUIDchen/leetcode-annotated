// 题目：3819. 非负元素轮替（Rotate Non Negative Elements）
// 思路：先把所有非负元素按原顺序取出成序列 t，轮替 k 次等价于把 t 循环移动 k 位，于是 t[i] 的新下标可以直接用 (i - k) 对 m 取模算出来；最后再按原数组顺序，把非负位置依次用轮替后的值覆盖回去。
// 时间复杂度：O(n)，三次线性遍历；空间复杂度：O(m)，m 为非负元素个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> rotateElements(vector<int>& nums, int k) {  // nums：原数组；k：轮替次数，返回轮替后的数组
        vector<int> t;  // t 按原顺序收集所有非负元素
        for (int x : nums) {  // 遍历原数组的每个元素
            if (x >= 0) {  // 只关心非负元素，负数位置保持不动
                t.push_back(x);  // 非负元素依次入列
            }
        }
        int m = t.size();  // m 是非负元素的个数，也是轮替的周期
        vector<int> d(m);  // d 保存轮替后每个非负元素的新值
        for (int i = 0; i < m; i++) {  // 枚举 t 中的每个元素
            d[((i - k) % m + m) % m] = t[i];  // 轮替 k 位后 t[i] 的新下标是 (i - k) mod m；双重取模保证下标非负，且 k 很大时也安全
        }
        int j = 0;  // j 指向 d 中下一个待取出的元素
        for (int i = 0; i < nums.size(); i++) {  // 按原数组顺序回填
            if (nums[i] >= 0) {  // 只覆盖非负元素所在的位置
                nums[i] = d[j++];  // 用轮替后的值覆盖该位置，并让 j 后移一位
            }
        }
        return nums;  // 返回原地修改后的数组
    }
};
