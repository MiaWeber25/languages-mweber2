# https://github.com/ocaml/infrastructure/wiki/Containers
FROM ocaml/opam2:ubuntu-lts

RUN sudo apt-get update \
 && DEBIAN_FRONTEND=noninteractive sudo apt-get install -y \
    				   time curl build-essential gdb cmake git nano python3 emacs-nox vim dos2unix \
 && sudo apt-get clean \
 && sudo /bin/rm -rf /var/lib/apt/lists/*

RUN sudo mkdir -p /app && chown $USER:$USER /app
WORKDIR /app
EXPOSE 8000

RUN echo  export PATH='"'/app/_build/default:/app/bin:/app/bin/$(uname -s)-$(uname -m):/app/node_modules/.bin:/app:'${PATH}''"' >> $HOME/.bashrc
RUN echo  'opam switch 4.10 > /dev/null' >> $HOME/.bashrc
RUN echo  'eval $(opam env)' >> $HOME/.bashrc
RUN opam install dune
# CMD ["ocaml","app.ml"]
ENTRYPOINT ["/bin/bash","-i","-c","\"$@\"","--"]
