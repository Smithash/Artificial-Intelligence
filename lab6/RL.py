import gymnasium as gym
import numpy as np
import matplotlib.pyplot as plt


#Each episode ends when done flag or 100 steps have elapsed
# at end of each episode, record the sum of rewards received for that episode
def Q_learning(env, epi = 0.1, gamma = 0.99, alpha = 0.1):
    n_observations = env.observation_space.n
    n_actions = env.action_space.n
    #Initialise Q to be zero for all o and a 
    qtable = np.zeros((n_observations, n_actions))
    
    rewards = []
    for _ in range(1000):
        curr_state = env.reset()[0]
        total_reward =0
        
        for _ in range(100):
            if np.random.uniform(0, 1) < epi:
                action = env.action_space.sample()
            else:
                action = np.argmax(qtable[curr_state])

            #Observe transition
            next_state, reward, done, _, _ = env.step(action)
            total_reward += reward

            #Select a' = argmax Q(s,b)
            best_action = np.argmax(qtable[next_state])
            
            qtable[curr_state, action] = qtable[curr_state, action] + alpha* (reward + gamma* (qtable[next_state, best_action] - qtable[curr_state, action]))
            curr_state = next_state
            
            if done:
                break
            
        rewards.append(total_reward)
    return rewards

def sarsa(env, epi = 0.1, gamma = 0.99, alpha = 0.1):
    n_observations = env.observation_space.n
    n_actions = env.action_space.n
    #Initialise Q to be zero for all o and a 
    qtable = np.zeros((n_observations, n_actions))
    rewards = []
    for _ in range(1000):
        #Observe s
        curr_state = env.reset()[0]
        total_reward =0
        #Select a using Q (epi greedy)
        if np.random.uniform(0, 1) < epi:
                action = env.action_space.sample()
        else:
            action = np.argmax(qtable[curr_state])
        
        for _ in range(100):
            #Observe transition
            next_state, reward, done, _, _ = env.step(action)
            total_reward += reward
            # select a' from s' using Q
            if np.random.uniform(0, 1) < epi:
                next_action = env.action_space.sample()
            else:
                next_action = np.argmax(qtable[next_state])
                
            qtable[curr_state, action] = qtable[curr_state, action] + alpha * (reward + gamma * (qtable[next_state, next_action] - qtable[curr_state,action]))

            curr_state = next_state
            action = next_action
            
            if done:
                break
        rewards.append(total_reward)  
        
    return rewards
        
# Run the entire procedure 10 times in total and average the results over thesse 10 runs.
# Will have a list of 1000, each entry represents the average returned for each episode
def run_experiments(algorithm, runs=10):
    env = gym.make('CliffWalking-v0')
    all_rewards = []

    for _ in range(runs):
        rewards = algorithm(env)
        all_rewards.append(rewards)

    average_rewards = np.mean(all_rewards, axis=0)
    return average_rewards

#Plot the results on same axes, label each line with relevant algorithm
def plot_results(q_learning_results, sarsa_results):
    plt.plot(q_learning_results, label='Q-Learning')
    plt.plot(sarsa_results, label='SARSA')
    plt.xlabel('Episodes')
    plt.ylabel('Average Reward')
    plt.title('Q-Learning vs SARSA on CliffWalking')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    qlearning_results = run_experiments(Q_learning)
    sarsa_learning_results = run_experiments(sarsa)
    plot_results(qlearning_results, sarsa_learning_results) 