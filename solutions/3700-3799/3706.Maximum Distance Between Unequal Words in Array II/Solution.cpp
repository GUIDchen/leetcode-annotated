// 3706. Maximum Distance Between Unequal Words in Array II（3706. 不同单词间的最大距离 II 🔒）
// 核心思路：最大距离只会出现在“与首词不同”或“与尾词不同”的配对中，一次遍历每个下标，分别与首词、尾词比较并更新最大距离即可。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int maxDistance(vector<string>& words) {  // 返回两个不同单词之间的最大下标距离
        int n = words.size();  // 单词总数
        int ans = 0;  // 记录当前最大距离
        for (int i = 0; i < n; ++i) {  // 从左到右枚举右端点下标 i
            if (words[i] != words[0]) {  // 若 words[i] 与首词不同，就能和下标 0 配对
                ans = max(ans, i + 1);  // 与下标 0 的距离为 i - 0 + 1 = i + 1
            }  // 结束首词配对判断
            if (words[i] != words[n - 1]) {  // 若 words[i] 与尾词不同，就能和下标 n - 1 配对
                ans = max(ans, n - i);  // 与下标 n - 1 的距离为 n - 1 - i + 1 = n - i
            }  // 结束尾词配对判断
        }  // 结束枚举
        return ans;  // 返回最大距离
    }  // 方法结束
};  // 类定义结束
