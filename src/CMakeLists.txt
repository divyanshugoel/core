# Basic elements.
add_subdirectory(core)
add_subdirectory(mathematics)
add_subdirectory(graph)
add_subdirectory(common)

# Utilities for plotting. 
add_subdirectory(plot)

# Handle the network module. 
add_subdirectory(network)

# For now this emulated wcs.
add_subdirectory(wcs)

# To store and load the system state. 
add_subdirectory(database)

# Combined things.
add_subdirectory(scene)
add_subdirectory(scenario)
add_subdirectory(simulation)

# Used for Front end.
add_subdirectory(fleet)
add_subdirectory(ui)

# Used for Visualisations.
add_subdirectory(editor)

# Executables.
add_subdirectory(fmsApp)
