// 题目：2682. 找出转圈游戏输家（Find the Losers of the Circular Game）
// 思路：模拟传圈过程，每步按当前步数 p*k 在环上前进，用 vis 标记已接到球的人；一旦走到已标记的位置就停止，未被标记的人即为输家。
// 时间复杂度：O(n)，每人最多被标记一次；空间复杂度：O(n)，vis 数组记录是否接过球。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> circularGameLosers(int n, int k) {  // n：人数；k：每轮步长的倍数
        bool vis[n];  // vis[i] 表示编号 i+1 的人是否接到过球
        memset(vis, false, sizeof(vis));  // 初始都未接过球，用 memset 快速清空
        for (int i = 0, p = 1; !vis[i]; ++p) {  // i：当前持球人下标，p：本轮步长倍数；持球人已接过球就结束
            vis[i] = true;  // 标记当前持球人已经接过球
            i = (i + p * k) % n;  // 在环上向前走 p*k 步，取模实现循环
        }  // 模拟结束，剩下的都是没接到球的人
        vector<int> ans;  // ans 收集输家的原始编号
        for (int i = 0; i < n; ++i) {  // 按下标从小到大扫描所有人
            if (!vis[i]) {  // 只处理从未接过球的人
                ans.push_back(i + 1);  // 题目编号从 1 开始，所以输出 i+1
            }  // 分支结束
        }  // 扫描结束
        return ans;  // 返回所有输家编号
    }  // 方法结束
};  // 类定义结束