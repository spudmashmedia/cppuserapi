# The Purpose of this Repository 
![why](/docs/img/why.jpg)

The majority of the repositories at Spudmash Media serve as Quickstart templates for your next software build.

## Project Objectives
- A production-ready REST API written in C++.
- Adhere to [Google's C++ Style Guide](https://google.github.io) (or a pragmatically loose version of it).
- Project setup and dependency management via [Vcpkg](https://vcpkg.io).
- Demonstrate performance and footprint improvements over other languages.

## Development Workflow
This repository is developed using:
- **Multiplexer**: tmux
- **Shell**: fish
- **Editor**: Helix (via LSP)
- **Language Standard**: C++20
- **Compiler**: Clang for development, GCC for the Docker image build stage.

## Thoughts

The most common complaints about C++ are:
- It's too hard to use.
- I have to manage my own memory.
- It's too verbose.
- I have to compile my code.
- Other languages provide best practices with enforced patterns.

As other languages have evolved, these complaints have started to become non-issues:

- **JavaScript to TypeScript**: You are already compiling code and strongly typing objects—this is fundamentally no different from C++. Furthermore, Node.js carries a V8 engine "warmup tax," whereas a C++ binary starts in milliseconds. Just as Node uses NPM, modern C++ uses **Vcpkg** for seamless package management.

- **Rust**: While Rust claims superior memory management through "ownership," C++ achieves similar results by following established rules for passing by pointer or reference. Following [RAII (Resource Acquisition Is Initialization)](https://en.cppreference.com) principles makes modern C++ memory management predictable and robust. Ultimately, the output binary sizes are comparable.

- **C# / Java**: Capabilities often assumed to be "free" in C# or Java—such as dependency injection and managed memory—can be replicated in C++. By following modern memory handling rules and architectural patterns, you get the same benefits without the runtime overhead.

- **Architecture**: Implementing Model-View-Controller (MVC) and employing Dependency Injection (DI) isn't difficult in C++... you just have to do it.

- **Footprint**: C++ binaries are significantly smaller than the artifacts produced by Java or C#. This is a massive advantage when pushing to pricey IaaS providers; those saved megabytes and CPU cycles directly impact the bottom line.

## Is It Worth the Hassle? 🧐

Technology choices often boil down to a team's existing capabilities:
- Does your crew only work with JavaScript/Node?
- Have you built services exclusively in C#, Java, Go, or Rust in the past?

Usually, this is where the conversation ends, and you proceed with what the team knows best.

As of March 2026, the market is flooded with LLMs and Agentic Coding Tools. We should start asking: "What will give this service the best possible performance, the smallest footprint, and the quickest load times?" Smaller images and faster response times equate to less money spent on IaaS. 

While these AI tools eventually perform the heavy lifting, we still need to "look under the hood" occasionally—so we might as well learn C++.

If performance and cost are the priority, why entertain other languages? 
- Modern C++ is no different from JavaScript, C#, or Java in terms of readability.
- The Standard Library is robust, and libraries like **Crow** and **Boost** are excellent alternatives to ASP.NET Core or Spring Boot.
- Tooling has a one-time "setup tax," but becomes simple when coupled with Vcpkg.
- You avoid the "ownership" complexities built into Rust while maintaining the same static compilation benefits.

The bottom line: Are you willing to trade a little convenience for massive performance? It might be time we start cleaning up our own memory... it's really not that hard.
