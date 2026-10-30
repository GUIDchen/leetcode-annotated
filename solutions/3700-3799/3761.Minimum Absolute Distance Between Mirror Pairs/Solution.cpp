// 3761. 镜像对之间最小绝对距离（Minimum Absolute Distance Between Mirror Pairs）
// 核心思路：一次遍历，把当前元素的镜像值 reverse(x) 与下标存入哈希表；下一个元素若命中表中键，说明它与之前某元素互为镜像，用下标差更新最小距离。
// 复杂度：时间 O(n × 数字位数)，空间 O(n)。
class Solution {  // 定义解法类
public:  // 公有接口
    int minMirrorPairDistance(vector<int>& nums) {  // 接口：返回镜像对之间的最小绝对距离
        int n = nums.size();  // n 为数组长度
        int ans = n + 1;  // ans 初始化为不可能达到的 n + 1，表示尚未找到镜像对
        unordered_map<int, int> pos;  // pos 记录“镜像值 -> 最近下标”
        auto reverse = [](int x) {  // lambda：求一个整数的十进制逆序值
            int y = 0;  // y 累积逆序结果
            for (; x > 0; x /= 10) {  // 不断取最低位并右移原数
                y = y * 10 + x % 10;  // 把当前最低位接到 y 的末尾
            }  // for 结束
            return y;  // 返回逆序后的数
        };  // lambda 定义结束
        for (int i = 0; i < n; ++i) {  // 从左到右枚举每个元素
            if (pos.contains(nums[i])) {  // 当前值若出现在表中，说明它等于之前某元素的镜像值
                ans = min(ans, i - pos[nums[i]]);  // 用下标差更新最小距离
            }  // if 结束
            pos[reverse(nums[i])] = i;  // 把当前元素的镜像值与下标登记，供后续元素匹配
        }  // for 结束
        return ans > n ? -1 : ans;  // 仍未更新过则返回 -1，否则返回最小距离
    }  // 方法结束
};  // 类定义结束
