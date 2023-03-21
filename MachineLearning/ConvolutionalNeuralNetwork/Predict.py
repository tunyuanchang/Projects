import numpy as np


# Helper function
def predict(X, y, model, classes):
    """
    This function is used to predict the results of a  L-layer neural network.
    
    Arguments:
    X -- data set of examples you would like to label
    model -- trained model
    classes - number of classes, 2 for binary classification, >2 for multi-class classification
    
    Returns:
    p -- predictions for the given dataset X
    """
    
    m = X.shape[0]
    n = len(model.layers) # number of layers in the neural network

    if classes == 2:
        p = np.zeros((1,m))
    else:
        p = np.zeros((classes, m))
    
    # Forward propagation
    probas = model.forward(X)
    
    if classes == 2:
      # convert probas to 0/1 predictions
      for i in range(0, probas.shape[1]):
        if probas[0,i] > 0.5:
            p[0,i] = 1
        else:
            p[0,i] = 0

      #print results
      if y is not None:
        print("Accuracy: "  + str(np.sum((p == y)/m)))

    else:
      # convert probas to one hot vector predictions
      prediction = np.argmax(probas, axis=0, out=None)
    
      for i in range(len(prediction)):
        p[prediction[i], i] = 1

      #print results
      if y is not None:
        correct = 0
        for i in range(m):
            if (p[:, i] == y[:, i]).all():
                correct += 1
        print("Accuracy: "  + str(correct/m))
        
    return p