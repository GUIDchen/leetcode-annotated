// 题目：1762. 能看到海景的建筑物（Buildings With an Ocean View）🔒
// 思路：从右往左扫描并维护右侧最高高度；当前建筑严格更高才看得到海，收下标后整体反转成升序。
// 时间复杂度：O(n)，一次扫描加一次反转；空间复杂度：O(n)，存放答案下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findBuildings(vector<int>& heights) {  // heights：从左到右的建筑高度
        vector<int> ans;  // 收集能看到海景的建筑下标
        int mx = 0;  // 当前已扫描到的右侧最高高度，海平面高度视为 0
        for (int i = heights.size() - 1; ~i; --i) {  // 从最右侧向左倒序遍历；~i 在 i 变为 -1 时为 0，用来结束循环
            if (heights[i] > mx) {  // 严格高于右侧所有建筑，视线不会被挡住
                ans.push_back(i);  // 记录该建筑下标，此时是按从右往左的顺序
                mx = heights[i];  // 更新右侧最高高度
            }
        }
        reverse(ans.begin(), ans.end());  // 反转成从左到右的下标顺序，符合题目要求
        return ans;  // 返回结果数组
    }
};