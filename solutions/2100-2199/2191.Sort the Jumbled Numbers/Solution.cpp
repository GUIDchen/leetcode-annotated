// 题目：2191. 将杂乱无章的数字排序（Sort the Jumbled Numbers）
// 思路：先用映射函数把每个数逐位替换成新数，再把 (映射值, 原下标) 排序，最后按顺序取回原数字。
// 时间复杂度：O(n log n + n log M)，M 为最大位数；空间复杂度：O(n)，额外保存映射值与下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {  // mapping：0~9 的新数字映射表；nums：待排序的数组
        auto f = [&](int x) {  // 映射函数：把整数 x 的每一位按 mapping 替换后重新拼成整数
            if (x == 0) {  // 特判 x 为 0：否则下面的循环一次都不会执行，得不到结果
                return mapping[0];  // 0 的映射值就是 mapping[0]
            }  // if 结束
            int y = 0;  // 映射后的新整数，由低位到高位逐步拼出
            for (int k = 1; x; x /= 10) {  // k 是当前位的权重（个位为 1），每轮把 x 的最低位移除
                int v = mapping[x % 10];  // 取出最低位数字，并换成映射后的新数字
                y = k * v + y;  // 把新数字放到权重为 k 的位置上，累加到结果
                k *= 10;  // 权重进位，准备处理更高一位
            }  // for 结束
            return y;  // 返回映射后的整数
        };  // lambda 定义结束
        const int n = nums.size();  // 数组元素个数
        vector<pair<int, int>> arr;  // 保存 (映射值, 原下标)；pair 默认比较先比映射值、再比下标
        for (int i = 0; i < n; ++i) {  // 遍历每一个元素
            arr.emplace_back(f(nums[i]), i);  // 就地构造二元组，避免额外的临时对象
        }  // for 结束
        sort(arr.begin(), arr.end());  // 按映射值升序排序；映射值相同时下标小的在前，保证排序稳定
        vector<int> ans;  // 保存排序后的原数字
        for (const auto& [_, i] : arr) {  // 结构化绑定：忽略映射值，只取出原下标
            ans.push_back(nums[i]);  // 按排好的顺序放回原数字
        }  // for 结束
        return ans;  // 返回结果数组
    }  // 方法结束
};  // 类定义结束