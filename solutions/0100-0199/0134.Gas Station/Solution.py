# 题目：134. 加油站（Gas Station）
# 思路：双指针在环上扩张窗口，右端顺时针加入加油站，净油量为负时把左端逆时针补进来；窗口覆盖一圈后的左端即答案。
# 时间复杂度：O(n)，每个站点最多被左右指针各访问一次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:  # 返回能绕行一周的起点下标，无解返回 -1
        n = len(gas)  # n 是加油站数量
        i = j = n - 1  # i 是窗口左端、j 是窗口右端，都从最后一站开始
        cnt = s = 0  # cnt 是窗口覆盖的站数，s 是窗口内的净油量
        while cnt < n:  # 窗口还没覆盖整圈就继续扩张
            s += gas[j] - cost[j]  # 右端 j 站并入窗口：加油量减去到下一站的耗油量
            cnt += 1  # 窗口长度加一
            j = (j + 1) % n  # 右端顺时针前进一格，取模实现环形
            while s < 0 and cnt < n:  # 净油量不足，说明起点要往前挪，于是向左端继续并入站点
                i -= 1  # 左端逆时针前进一格
                s += gas[i] - cost[i]  # 把新并入的 i 站计入净油量
                cnt += 1  # 窗口长度加一
        return -1 if s < 0 else i  # 总油量为负无解，否则左端 i 就是可行起点
