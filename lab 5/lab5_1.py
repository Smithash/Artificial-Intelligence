import numpy as np
import sys
#if it was raining yesterday, 70% chance it will rain today
#if it wasn't raining yesterdat, 30% chance it will rain today
#on rainy days, 90% of time neighbour had an umbrella
#on non-rainy days, 20% of time neighbour had an umbrella

#boolean state variable: rain or not rain today
#observation variable: neighbour leaves home with an umbrella

#Compute P(sn = Rain) where sn is the hidden variable at timestep n
#normalise probabilities at each step: divide by their sum

def HMM(observation_matrix, observations, transition):
    #forward algorithm 
    num_states =len(transition)
    max_time = len(observations) +1
    
    probabilities = np.zeros((num_states, max_time))
    
    for state in range(num_states):
        probabilities[state][0] = 1/num_states
    
    for t in range(1, max_time):
        sum =0
        for current_state in range(num_states):
            for previous_state in range(num_states):
                probabilities[current_state][t] += transition[current_state, previous_state] * probabilities[previous_state, t-1] 
            probabilities[current_state][t]*= observation_matrix[current_state, observations[t-1]]
            
            sum+= probabilities[current_state][t]
        
        #Normalises the probabilities at each time step
        for state in range(num_states):
            probabilities[state][t] = probabilities[state][t] /sum 

    return probabilities


#input:
#single line containing 0s and 1s separated by a step

user_input = input()
observations = list(map(int, user_input.split()))

transition = np.array([[0.7, 0.3],[0.3, 0.7]])
observation_matrix = np.array([[0.8, 0.2], [0.1, 0.9]])

#2D array where each row is a state value and each column is a timestep
probabilites = HMM(observation_matrix, observations, transition)
#output:
#for each time step, output probability that it is raining
for t in range(0, len(observations) +1):
    print(f'Timestep {t}: {round(probabilites[1][t], 3)}')