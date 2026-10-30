// 题目：2094. 找出 3 位偶数（Finding 3-Digit Even Numbers）
// 思路：统计 digits 里每个数字的可用次数，再枚举 100~999 的所有偶数，逐一检查其数位需求是否被满足。
// 时间复杂度：O(n + 900·10)，枚举 900 个三位偶数；空间复杂度：O(1)，只有两个长度为 10 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findEvenNumbers(vector<int>& digits) {  // digits：可以使用的数字，每个数字用一次就少一次
        int cnt[10]{};  // cnt[d] 记录数字 d 在 digits 中的可用次数
        for (int x : digits) {  // 遍历给定的每个数字
            ++cnt[x];  // 累计该数字的可用次数
        }
        vector<int> ans;  // 结果从小到大收集
        for (int x = 100; x < 1000; x += 2) {  // 枚举所有三位偶数（步长 2 保证末位为偶）
            int cnt1[10]{};  // cnt1 统计当前数 x 用掉了各数字多少次
            for (int y = x; y; y /= 10) {  // 逐位拆解 x
                ++cnt1[y % 10];  // 最低位的计数加一
            }
            bool ok = true;  // 先假定 x 可以用 digits 拼出来
            for (int i = 0; i < 10 && ok; ++i) {  // 逐位比对可用量，一旦不够就提前退出
                ok = cnt[i] >= cnt1[i];  // 该数字的需求量不能超过可用量
            }
            if (ok) {  // 所有数字的用量都不超限
                ans.push_back(x);  // x 合法，按升序加入答案
            }
        }
        return ans;  // 返回所有能拼出的三位偶数
    }
};