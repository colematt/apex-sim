# Simulator variables
CXX=clang++
CXXFLAGS = -std=c++11 -g -Wall
CXX_INCLUDE = -I./srcs

# Apex variables
APEX_SRC = srcs
CLASS_FILES = \
	$(APEX_SRC)/apex.cpp \
	$(APEX_SRC)/code.cpp \
	$(APEX_SRC)/cpu.cpp \
	$(APEX_SRC)/data.cpp \
	$(APEX_SRC)/register.cpp \
	$(APEX_SRC)/simulate.cpp \
	$(APEX_SRC)/stage.cpp

# LaTeX variables
PAPERNAME = report2
TEXFILES = *.tex *.bib


all: apex-sim $(PAPERNAME).pdf

apex-sim:
	$(CXX) $(CXX_INCLUDE) $(CXXFLAGS) srcs/main.cpp $(CLASS_FILES) -o apex-sim

$(PAPERNAME).pdf: $(TEXFILES)
	pdflatex $(PAPERNAME).tex
	bibtex $(PAPERNAME)
	pdflatex $(PAPERNAME).tex
	pdflatex $(PAPERNAME).tex

.PHONY: clean
clean:
	rm -rfv *~ *.o
	rm -fv apex-sim
	rm -fv $(PAPERNAME).out *.dvi *.aux *.log *.blg *.bbl *.bak *~
