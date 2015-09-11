"""This module provides a class to create documentation automatically."""

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python
import sys

from path import Path

# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('SphinxProject',)


# =============================================================================
# >> CLASSES
# =============================================================================
class SphinxProject(object):

    """Representation of a Sphinx project."""

    def __init__(self, package_dir, project_dir):
        """Initialize the Sphinx project object.

        :param str package_dir: The path to the package to document.
        :param str project_dir: The path to the Sphinx project or where it
            should be saved.
        """
        self._package_dir = Path(package_dir)
        self._project_dir = Path(project_dir)
        self.validate_package()

    @property
    def project_dir(self):
        """Return the project directory as a Path object."""
        return self._project_dir

    @property
    def project_source_dir(self):
        """Return the project source directory."""
        return self.project_dir / 'source'

    @property
    def project_build_dir(self):
        """Return the project build directory."""
        return self.project_dir / 'build'

    @property
    def package_dir(self):
        """Return the package directory as a Path object."""
        return self._package_dir

    def project_exists(self):
        """Return True if the Sphinx project exists."""
        return self.project_dir.isdir()

    def package_exists(self):
        """Return True if the package exists."""
        return self.package_dir.isdir()

    def create(self, author, project_name=None, version='1'):
        """Create a new Sphinx project.

        :param str author: Name of the package author.
        :param str project_name: Name of the project that is displayed in the
            documentation. If None, it will be the name of the package.
        :param str version: Project/package version.
        """
        if self.project_exists():
            raise ValueError('The project already exists.')

        self.validate_package()
        self.project_dir.mkdir()

        from sphinx.quickstart import main

        argv = [
            '', # Will be skipped.
            '-q', # Don't start the interactive mode
        ]

        if project_name is None:
            project_name = self.package_dir.namebase

        argv.append('-p {0}'.format(project_name))
        argv.append('-a {0}'.format(author))
        argv.append('-v {0}'.format(version))

        argv.extend([
            str(self.project_dir),
            '--sep', # Separate source and build directory
            '--ext-autodoc', # Enable autodoc
            '--no-makefile',
            '--no-batchfile'
        ])

        # Hacky, but required, because sphinx is reading sys.argv even if you
        # pass a list to main()
        old_argv = sys.argv
        sys.argv = argv
        try:
            main(sys.argv)
        except:
            raise
        finally:
            sys.argv = old_argv

    def generate_project_files(self):
        """Generate the project files (*.rst files)."""
        self.validate_project_and_package()

        from sphinx.apidoc import main
        argv = [
            '', # Will be skipped.
            '-e', # Separate pages/files for every module
            '-o',
            str(self.project_source_dir),
            str(self.package_dir), # Package to document
            str(self.project_dir), # Exclude the project directory
        ]

        # Hacky, but required, because sphinx is reading sys.argv even if you
        # pass a list to main()
        old_argv = sys.argv
        sys.argv = argv
        try:
            main(sys.argv)
        except:
            raise
        finally:
            sys.argv = old_argv

    def build(self):
        """Build the Sphinx project."""
        self.validate_project_and_package()

        added_to_path = self.package_dir in sys.path
        if not added_to_path:
            sys.path.append(str(self.package_dir.parent))

        from sphinx import main
        argv = [
            '', # Will be skipped.
            str(self.project_source_dir),
            str(self.project_build_dir),
        ]

        # Hacky, but required, because sphinx is reading sys.argv even if you
        # pass a list to main()
        old_argv = sys.argv
        sys.argv = argv
        try:
            main(sys.argv)
        except SystemExit as e:
            if e.code != 0:
                raise
        finally:
            sys.argv = old_argv
            if added_to_path:
                sys.path.remove(str(self.package_dir.parent))

    def validate_project_and_package(self):
        """Raise a ValueError if the project or package does not exist."""
        self.validate_project()
        self.validate_package()

    def validate_project(self):
        """Raise a ValueError if the project does not exist."""
        if not self.project_exists():
            raise ValueError(
                'Create the project before generating project files.')

    def validate_package(self):
        """Raise a ValueError if the package does not exist."""
        if not self.package_exists():
            raise ValueError('The package does not exist.')
