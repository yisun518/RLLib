/*
 * GQTest.h
 *
 *  Created on: Nov 6, 2013
 *      Author: sam
 */

#ifndef GQTEST_H_
#define GQTEST_H_

#include "HeaderTest.h"

class OffPolicyLearnerFactory
{
  public:
    virtual ~OffPolicyLearnerFactory()
    {
    }
    virtual OffPolicyControlLearner<double>* createLearner(ActionList* actions,
        StateToStateAction<double>* toStateAction, Policy<double>* target,
        Policy<double>* behavior) =0;

    virtual double getBeta() const =0;
    virtual double getLambda() const =0;
};

class GreedyGQFactory: public OffPolicyLearnerFactory
{
  private:
    double beta;
    double alpha_theta;
    double alpha_w;
    double lambda;

    std::vector<Predictor<double>*> predictors;
    std::vector<OffPolicyControlLearner<double>*> offPolicyControlLearners;
    std::vector<Trace<double>*> traces;

  public:
    GreedyGQFactory(const double& beta, const double& alpha_theta, const double& alpha_w,
        const double& lambda);
    ~GreedyGQFactory();

    OffPolicyControlLearner<double>* createLearner(ActionList* actions,
        StateToStateAction<double>* toStateAction, Policy<double>* target,
        Policy<double>* behavior);
    double getBeta() const;
    double getLambda() const;
};

RLLIB_TEST(GQTest)
class GQTest: public GQTestBase
{
  public:
    void run();
  private:
    void testOnPolicyGQ();
    void testOffPolicyGQ();
    void testGQOnRandomWalk(const double& targetLeftProbability,
        const double& behaviourLeftProbability, OffPolicyLearnerFactory* learnerFactory);
    void computeValueFunction(const OffPolicyControlLearner<double>* learner,
        const FSGAgentState<>* agentState, Vector<double>* vFun);

};

#endif /* GQTEST_H_ */
