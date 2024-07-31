import random

class Rabbit:
    global rabbit_counter
    rabbit_counter = 1

    def __init__(self, name, age, gender):
        self.name = name
        self.age = age
        self.gender = gender
        self.cooldown = 0  # Cooldown in years

    def can_mate(self, other_rabbit):
        return (
            self.gender != other_rabbit.gender
            and self.age >= 4
            and other_rabbit.age >= 4
            and self.cooldown == 0
        )

    def mate(self, other_rabbit):
        if self.can_mate(other_rabbit):
            # Introduce a 50% chance of successful mating
            if random.random() < 0.5:
                global rabbit_counter
                baby_name = f"{rabbit_counter}"
                rabbit_counter += 1
                baby_age = 0
                baby_gender = random.choice(['Male', 'Female'])
                baby_rabbit = Rabbit(baby_name, baby_age, baby_gender)
                self.cooldown = 1  # Set cooldown to 1 year
                return baby_rabbit
            else:
                pass
        else:
            pass

    def age_one_year(self):
        self.age += 1
        if self.cooldown > 0:
            self.cooldown -= 1

# Simulation
rabbit_population = []
predators = 0
food_sources = 0
kits_born = 0
predator_deaths = 0
years_passed = 0
event_counter = 0  # Counter for triggering events every 10 years

def introduce_new_rabbits():
    print("Introducing a new food source! Adding 2 rabbits permanently.")
    global rabbit_population
    global rabbit_counter
    new_rabbits = [Rabbit(str(rabbit_counter), 0, random.choice(['Male', 'Female'])) for _ in range(2)]
    rabbit_population.extend(new_rabbits)
    rabbit_counter += 2

def introduce_predator():
    print("Introducing a predator! It will eat one rabbit every 3 years.")
    global predators
    predators += 1

def rabbit_gives_birth():
    print(f"{rabbit.name} gave birth to two kits!")
    global kits_born
    kits_born += 2

def predator_dies():
    print("A predator has died.")
    global predators, predator_deaths
    predators -= 1
    predator_deaths += 1

# Initial population
rabbit_population.append(Rabbit("Alice", 6, "Female"))
rabbit_population.append(Rabbit("Bob", 7, "Male"))
rabbit_population.append(Rabbit("Charlie", 5, "Male"))

# Run simulation for 15 time steps (years)
for time_step in range(1500):
    print(f"\n--- Time Step {time_step + 1} ---")

    # Check if 10 years have passed to trigger events
    if event_counter == 10:
        chance = random.random()
        if chance < 0.25:
            introduce_new_rabbits()
            food_sources += 1
        elif chance < 0.75:
            introduce_predator()
        elif chance < 0.9:
            rabbit_gives_birth()
        else:
            predator_dies()

        # Reset the event counter
        event_counter = 0
    else:
        event_counter += 1

    # Pair random rabbits for potential mating
    random.shuffle(rabbit_population)
    for i in range(0, len(rabbit_population), 2):
        if i + 1 < len(rabbit_population):
            rabbit1 = rabbit_population[i]
            rabbit2 = rabbit_population[i + 1]
            baby_rabbit = rabbit1.mate(rabbit2)
            if baby_rabbit:
                rabbit_population.append(baby_rabbit)

    # Age the rabbits and update cooldown
    for rabbit in rabbit_population:
        rabbit.age_one_year()

    # Remove rabbits older than 15 years
    rabbit_population = [rabbit for rabbit in rabbit_population if rabbit.age <= 15]

    # Count the number of rabbits at each age
    age_counts = {}
    for rabbit in rabbit_population:
        if rabbit.age not in age_counts:
            age_counts[rabbit.age] = 1
        else:
            age_counts[rabbit.age] += 1

    # Print the number of predators, food sources, kits born, and predator deaths
    print(f"Predators: {predators}, Food Sources: {food_sources}, Kits Born: {kits_born}, Predator Deaths: {predator_deaths}")
    print(f"Rabbits: {rabbit_counter}")

    # Increment years passed
    years_passed += 1

print(f"\nSimulation completed. Total years passed: {years_passed}")
