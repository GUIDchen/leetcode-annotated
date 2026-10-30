// 题目：4093. 至多 K 次数字重排后的最大和（Maximize Sum After At Most K Digit Rearrangements）
// 思路：先用辅助 lambda 把每个数的十进制数字降序重排，得到同位数下尽可能大的值 t[i]，重排收益就是 t[i] - nums[i]；把下标按收益降序排序，只给收益最大的前 k 个做重排（收益非负，用满 k 次不吃亏），其余保留原值，求和即为最大总和。
// 时间复杂度：O(n * 10 + n log n)，逐个拆位重排是每个数 O(10)，主要开销是排序；空间复杂度：O(n)，需要 t 与 ids 两个辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximizeSum(vector<int>& nums, int k) {  // nums：原始数组；k：至多可重排的元素个数；返回重排后的最大元素之和
        auto f = [](int x) {  // 辅助 lambda：把 x 的十进制数字降序重排，得到同位数下尽量大的数
            int cnt[10] = {};  // cnt[d]：数字 d 在 x 的十进制表示中出现的次数
            while (x) {  // 逐位拆分 x
                int v = x % 10;  // v 是当前最低位数字
                x /= 10;  // 去掉已经处理的最低位
                cnt[v]++;  // 该数字的出现次数加一
            }  // 拆位结束
            int y = 0;  // y 用来拼出降序重排后的新数
            for (int i = 9; i >= 0; i--) {  // 从大到小枚举数字，保证高位尽量大
                for (int j = 0; j < cnt[i]; j++) {  // 数字 i 出现几次就放几位
                    y = y * 10 + i;  // 把数字 i 追加到 y 的末尾
                }  // 数字 i 处理完毕
            }  // 所有数字拼接完毕
            return y;  // 返回重排后的最大数（x 为 0 时 y 也为 0，恰好正确）
        };  // lambda 定义结束
        int n = nums.size();  // n 是数组长度
        vector<int> t(n);  // t[i] 是 nums[i] 降序重排后的值
        vector<int> ids(n);  // ids 存放待排序的下标
        iota(ids.begin(), ids.end(), 0);  // 把 ids 依次填成 0,1,...,n-1
        for (int i = 0; i < n; i++) {  // 逐个计算重排后的值
            t[i] = f(nums[i]);  // 缓存重排结果，避免排序比较时重复计算
        }  // 预处理结束
        sort(ids.begin(), ids.end(), [&](int i, int j) {  // 按「重排收益」降序排列下标
            return t[i] - nums[i] > t[j] - nums[j];  // 收益大的下标排在前面
        });  // 排序结束
        long long ans = 0;  // ans 累计最终总和，量级可能超过 int
        for (int i = 0; i < n; i++) {  // 按收益从大到小依次决定是否重排
            int x = nums[ids[i]];  // 取出该下标的原始值
            ans += i < k ? t[ids[i]] : x;  // 前 k 个（收益最大）用重排后的值，其余保留原值
        }  // 求和结束
        return ans;  // 返回重排后的最大总和
    }  // 方法结束
};  // 类定义结束