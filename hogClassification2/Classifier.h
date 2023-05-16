#ifndef UUID1192847280736
#define UUID1192847280736

/**
  * RandomForestClassifier(base_estimator=DecisionTreeClassifier(), bootstrap=True, ccp_alpha=0.0, class_name=RandomForestClassifier, class_weight=None, criterion=gini, estimator_params=('criterion', 'max_depth', 'min_samples_split', 'min_samples_leaf', 'min_weight_fraction_leaf', 'max_features', 'max_leaf_nodes', 'min_impurity_decrease', 'random_state', 'ccp_alpha'), max_depth=40, max_features=auto, max_leaf_nodes=None, max_samples=None, min_impurity_decrease=0.0, min_samples_leaf=1, min_samples_split=2, min_weight_fraction_leaf=0.0, n_estimators=10, n_jobs=None, num_outputs=2, oob_score=False, package_name=everywhereml.sklearn.ensemble, random_state=None, template_folder=everywhereml/sklearn/ensemble, verbose=0, warm_start=False)
 */
class RandomForestClassifier {
    public:

        /**
         * Predict class from features
         */
        int predict(float *x) {
            int predictedValue = 0;
            size_t startedAt = micros();

            
    uint16_t votes[2] = { 0 };
    uint8_t classIdx = 0;
    float classScore = 0;

    
        tree0(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree1(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree2(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree3(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree4(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree5(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree6(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree7(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree8(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    
        tree9(x, &classIdx, &classScore);
        votes[classIdx] += classScore;
    

    // return argmax of votes
uint8_t maxClassIdx = 0;
float maxVote = votes[0];

for (uint8_t i = 1; i < 2; i++) {
    if (votes[i] > maxVote) {
        maxClassIdx = i;
        maxVote = votes[i];
    }
}

predictedValue = maxClassIdx;


            latency = micros() - startedAt;

            return (lastPrediction = predictedValue);
        }


        

/**
 * Predict class label
 */
String predictLabel(float *x) {
    return getLabelOf(predict(x));
}

/**
 * Get label of last prediction
 */
String getLabel() {
    return getLabelOf(lastPrediction);
}

/**
 * Get label of given class
 */
String getLabelOf(int8_t idx) {
    switch (idx) {
        case -1:
            return "ERROR";
        
            case 0:
                return "niks";
        
            case 1:
                return "gezicht";
        
        default:
            return "UNKNOWN";
    }
}


        /**
 * Get latency in micros
 */
uint32_t latencyInMicros() {
    return latency;
}

/**
 * Get latency in millis
 */
uint16_t latencyInMillis() {
    return latency / 1000;
}

    protected:
        float latency = 0;
        int lastPrediction = 0;

        

    
        
            /**
             * Random forest's tree #0
             */
            void tree0(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[63] <= 0.122654207054361) {
        
            
    *classIdx = 0;
    *classScore = 1122.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 638.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #1
             */
            void tree1(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[107] <= 0.024566521868109703) {
        
            
    if (x[125] <= 0.28306426107883453) {
        
            
    if (x[0] <= 0.367066303268075) {
        
            
    *classIdx = 0;
    *classScore = 1089.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 671.0;
    return;

        
    }

        
    }
    else {
        
            
    *classIdx = 0;
    *classScore = 1089.0;
    return;

        
    }

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 671.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #2
             */
            void tree2(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[128] <= 0.013638493604958057) {
        
            
    if (x[11] <= 0.0737021267414093) {
        
            
    *classIdx = 1;
    *classScore = 684.0;
    return;

        
    }
    else {
        
            
    if (x[88] <= 0.738336369395256) {
        
            
    *classIdx = 0;
    *classScore = 1076.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 684.0;
    return;

        
    }

        
    }

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 684.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #3
             */
            void tree3(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[62] <= 0.038512397557497025) {
        
            
    if (x[70] <= 0.19788962602615356) {
        
            
    *classIdx = 0;
    *classScore = 1090.0;
    return;

        
    }
    else {
        
            
    if (x[24] <= 0.24722697958350182) {
        
            
    *classIdx = 0;
    *classScore = 1090.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 670.0;
    return;

        
    }

        
    }

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 670.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #4
             */
            void tree4(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[18] <= 0.04677623137831688) {
        
            
    if (x[24] <= 0.3073648661375046) {
        
            
    *classIdx = 0;
    *classScore = 1079.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 681.0;
    return;

        
    }

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 681.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #5
             */
            void tree5(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[106] <= 0.015592938289046288) {
        
            
    if (x[2] <= 0.9001865983009338) {
        
            
    *classIdx = 0;
    *classScore = 1099.0;
    return;

        
    }
    else {
        
            
    if (x[82] <= 0.06041591987013817) {
        
            
    *classIdx = 0;
    *classScore = 1099.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 661.0;
    return;

        
    }

        
    }

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 661.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #6
             */
            void tree6(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[63] <= 0.10539184510707855) {
        
            
    if (x[14] <= 0.07370244339108467) {
        
            
    *classIdx = 0;
    *classScore = 1103.0;
    return;

        
    }
    else {
        
            
    if (x[127] <= 0.027816662564873695) {
        
            
    *classIdx = 0;
    *classScore = 1103.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 657.0;
    return;

        
    }

        
    }

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 657.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #7
             */
            void tree7(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[18] <= 0.04597491770982742) {
        
            
    if (x[129] <= 0.007079015485942364) {
        
            
    *classIdx = 0;
    *classScore = 1090.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 670.0;
    return;

        
    }

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 670.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #8
             */
            void tree8(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[26] <= 0.019520753994584084) {
        
            
    *classIdx = 0;
    *classScore = 1065.0;
    return;

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 695.0;
    return;

        
    }

            }
        
    
        
            /**
             * Random forest's tree #9
             */
            void tree9(float *x, uint8_t *classIdx, float *classScore) {
                
    if (x[128] <= 0.013236939907073975) {
        
            
    if (x[57] <= 0.0537747647613287) {
        
            
    *classIdx = 1;
    *classScore = 687.0;
    return;

        
    }
    else {
        
            
    *classIdx = 0;
    *classScore = 1073.0;
    return;

        
    }

        
    }
    else {
        
            
    if (x[55] <= 0.11825932562351227) {
        
            
    if (x[79] <= 0.5965680629014969) {
        
            
    *classIdx = 1;
    *classScore = 687.0;
    return;

        
    }
    else {
        
            
    *classIdx = 0;
    *classScore = 1073.0;
    return;

        
    }

        
    }
    else {
        
            
    *classIdx = 1;
    *classScore = 687.0;
    return;

        
    }

        
    }

            }
        
    


};



static RandomForestClassifier classifier;


#endif