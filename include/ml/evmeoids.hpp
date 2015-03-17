/*
 * =====================================================================================
 *
 *       Filename:  evmeoids.hpp
 *
 *    Description:  K centers classification
 *
 *        Version:  1.0
 *        Created:  2015年03月08日 17时02分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef EVMEOIDS_H
#define EVMEOIDS_H

#include <vector>
#include <set>

class EVMeoids
{
public:
    EVMeoids();
    void GetData(int num);
    bool FindNewCenter();
    int Closet(int num);  /*计算属于哪个分类*/
    double CalCost(std::set<double>& s);  /*计算总成本*/
    std::vector<int> data;
    int m_iClusterNum;
    std::vector<double> m_vCenter;
    std::vector<std::set<double> > m_vCluster;

};

#endif

